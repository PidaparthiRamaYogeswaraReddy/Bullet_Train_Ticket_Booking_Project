#include "railway.h"

/* Module 2 manages seat inventory and fare calculations. */
int count_available_seats(int train_id, const char *date, const char *travel_class) {
    int i, booked = 0, capacity = strcmp(travel_class, "Executive") == 0 ? EXECUTIVE_SEATS : ECONOMIC_SEATS;
    for (i = 0; i < booking_count; i++)
        if (bookings[i].active && bookings[i].train_id == train_id &&
            strcmp(bookings[i].journey_date, date) == 0 && strcmp(bookings[i].travel_class, travel_class) == 0) booked++;
    return capacity - booked;
}

int find_available_seat(int train_id, const char *date, const char *travel_class) {
    int seat, start, end, i, occupied;
    if (strcmp(travel_class, "Executive") == 0) { start = 1; end = EXECUTIVE_SEATS; }
    else { start = EXECUTIVE_SEATS + 1; end = TOTAL_SEATS; }
    for (seat = start; seat <= end; seat++) {
        occupied = 0;
        for (i = 0; i < booking_count; i++)
            if (bookings[i].active && bookings[i].train_id == train_id && bookings[i].seat_number == seat &&
                strcmp(bookings[i].journey_date, date) == 0) { occupied = 1; break; }
        if (!occupied) return seat;
    }
    return -1;
}

double calculate_fare(int source, int destination, const char *travel_class) {
    double rate = strcmp(travel_class, "Executive") == 0 ? executive_rate : economic_rate;
    return calculate_distance(source, destination) * rate * 1.05;
}

static int choose_route(int *direction, int *source, int *destination) {
    int i;
    printf("1. Chennai to Delhi\n2. Delhi to Chennai\n");
    *direction = read_int("Choose direction: ", 1, 2) - 1;
    printf("\nStations:\n");
    for (i = 0; i < TOTAL_STATIONS; i++) printf("%2d. %s\n", i + 1, stations[i].name);
    *source = read_int("Source station number: ", 1, TOTAL_STATIONS) - 1;
    *destination = read_int("Destination station number: ", 1, TOTAL_STATIONS) - 1;
    if (!validate_route_for_direction(*direction, *source, *destination)) {
        printf("Invalid route for the selected direction.\n"); return 0;
    }
    return 1;
}

static int choose_train(int direction) {
    int i, id, index;
    printf("\nAvailable trains:\n");
    for (i = 0; i < TOTAL_TRAINS; i++) if (trains[i].direction == direction)
        printf("ID %d | %s | Departure %s\n", trains[i].id, trains[i].name, trains[i].departure);
    id = read_int("Enter train ID: ", 1, TOTAL_TRAINS); index = find_train_by_id(id);
    if (index < 0 || trains[index].direction != direction) { printf("Train does not serve this direction.\n"); return -1; }
    return id;
}

static void collect_passenger_details(Booking *b) {
    read_line("Passenger full name: ", b->passenger_name, sizeof(b->passenger_name));
    while (strlen(b->passenger_name) == 0) read_line("Name cannot be empty. Enter name: ", b->passenger_name, sizeof(b->passenger_name));
    b->age = read_int("Passenger age: ", 1, 120);
    read_line("Gender: ", b->gender, sizeof(b->gender));
    if (strlen(b->gender) == 0) strcpy(b->gender, "Not specified");
    read_line("Mobile number: ", b->mobile, sizeof(b->mobile));
    if (strlen(b->mobile) == 0) strcpy(b->mobile, "Not provided");
}

static int choose_class_and_seat(Booking *b, const char *date) {
    int option, available;
    printf("1. Executive (Rs. %.2f/km)\n2. Economic (Rs. %.2f/km)\n", executive_rate, economic_rate);
    option = read_int("Select class: ", 1, 2);
    strcpy(b->travel_class, option == 1 ? "Executive" : "Economic");
    available = count_available_seats(b->train_id, date, b->travel_class);
    printf("Available seats: %d\n", available);
    if (available <= 0) { printf("This class is full for the selected train and date.\n"); return 0; }
    b->seat_number = find_available_seat(b->train_id, date, b->travel_class);
    return b->seat_number > 0;
}

void booking_module(void) {
    Booking b; int direction, source, destination, train_id; char date[MAX_DATE];
    printf("\n========== MODULE 2: PASSENGER & BOOKING ==========\n");
    if (booking_count >= MAX_BOOKINGS) { printf("Booking storage is full.\n"); pause_screen(); return; }
    if (!choose_route(&direction, &source, &destination)) { pause_screen(); return; }
    train_id = choose_train(direction); if (train_id < 0) { pause_screen(); return; }
    do { read_line("Journey date (DD-MM-YYYY): ", date, sizeof(date));
         if (!valid_future_date(date)) printf("Invalid date or date is in the past. Try again.\n");
    } while (!valid_future_date(date));
    memset(&b, 0, sizeof(b)); b.train_id = train_id;
    if (!choose_class_and_seat(&b, date)) { pause_screen(); return; }
    collect_passenger_details(&b);
    b.source_index = source; b.destination_index = destination; strcpy(b.journey_date, date);
    b.distance_km = calculate_distance(source, destination); b.fare = calculate_fare(source, destination, b.travel_class); b.active = 1;
    generate_pnr(b.pnr); bookings[booking_count++] = b; save_bookings();
    printf("\nBooking successful!\n"); print_booking(&b);
    printf("Remaining seats in this class: %d\n", count_available_seats(train_id, date, b.travel_class));
    pause_screen();
}
