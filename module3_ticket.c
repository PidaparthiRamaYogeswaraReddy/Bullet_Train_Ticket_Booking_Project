#include "railway.h"

/* MODULE 3: TICKET AND PNR MANAGEMENT */

int find_booking_by_pnr(const char *pnr) {
    int i;
    for (i = 0; i < booking_count; i++)
        if (bookings[i].active && strcmp(bookings[i].pnr, pnr) == 0) return i;
    return -1;
}

void generate_pnr(char *pnr) {
    static unsigned int serial = 1000;
    int i, duplicate;
    do {
        sprintf(pnr, "BT%06u", serial++);
        duplicate = 0;
        for (i = 0; i < booking_count; i++)
            if (strcmp(bookings[i].pnr, pnr) == 0) duplicate = 1;
    } while (duplicate);
}

void print_booking(const Booking *b) {
    int index = find_train_by_id(b->train_id);
    printf("\n========== BULLET TRAIN E-TICKET ==========\n");
    printf("PNR          : %s\n", b->pnr);
    printf("Passenger    : %s\n", b->passenger_name);
    printf("Age/Gender   : %d / %s\n", b->age, b->gender);
    printf("Mobile       : %s\n", b->mobile);
    printf("Train        : %s (ID %d)\n", index >= 0 ? trains[index].name : "Unknown", b->train_id);
    printf("From         : %s\n", stations[b->source_index].name);
    printf("To           : %s\n", stations[b->destination_index].name);
    printf("Journey date : %s\n", b->journey_date);
    printf("Class / Seat : %s / %d\n", b->travel_class, b->seat_number);
    printf("Distance     : %.0f km\n", b->distance_km);
    printf("Fare         : Rs. %.2f\n", b->fare);
    printf("Status       : %s\n", b->active ? "CONFIRMED" : "CANCELLED");
    printf("===========================================\n");
}

void search_ticket(void) {
    char pnr[MAX_PNR];
    int index;
    read_line("Enter PNR: ", pnr, sizeof(pnr));
    index = find_booking_by_pnr(pnr);
    if (index < 0) printf("No active ticket found for this PNR.\n");
    else print_booking(&bookings[index]);
}

void booking_history(void) {
    char name[MAX_NAME];
    int i, found = 0;
    read_line("Enter passenger name: ", name, sizeof(name));
    printf("\n%-12s %-20s %-12s %-12s %s\n", "PNR", "Passenger", "Date", "Class", "Fare");
    for (i = 0; i < booking_count; i++) {
        if (bookings[i].active && strcmp(bookings[i].passenger_name, name) == 0) {
            printf("%-12s %-20.20s %-12s %-12s Rs.%.2f\n", bookings[i].pnr,
                   bookings[i].passenger_name, bookings[i].journey_date,
                   bookings[i].travel_class, bookings[i].fare);
            found++;
        }
    }
    if (!found) printf("No active booking history found.\n");
    else printf("Total active tickets: %d\n", found);
}

void modify_ticket(void) {
    char pnr[MAX_PNR], date[MAX_DATE];
    int index, seat;
    read_line("Enter PNR to modify: ", pnr, sizeof(pnr));
    index = find_booking_by_pnr(pnr);
    if (index < 0) { printf("Active ticket not found.\n"); return; }
    print_booking(&bookings[index]);
    do {
        read_line("Enter new date (DD-MM-YYYY): ", date, sizeof(date));
        if (!valid_future_date(date)) printf("Enter a valid future date.\n");
    } while (!valid_future_date(date));
    if (count_available_seats(bookings[index].train_id, date, bookings[index].travel_class) <= 0) {
        printf("No seats available for that date.\n"); return;
    }
    seat = find_available_seat(bookings[index].train_id, date, bookings[index].travel_class);
    if (seat < 0) { printf("Seat allocation failed. No changes made.\n"); return; }
    bookings[index].seat_number = seat;
    strcpy(bookings[index].journey_date, date);
    save_bookings();
    printf("Ticket modified successfully. New seat: %d\n", seat);
    print_booking(&bookings[index]);
}

void ticket_module(void) {
    int choice;
    do {
        printf("\n========== MODULE 3: TICKET & PNR ==========\n");
        printf("1. Search ticket using PNR\n2. Booking history by passenger name\n");
        printf("3. Modify journey date\n4. Back to main menu\n");
        choice = read_int("Choose: ", 1, 4);
        if (choice == 1) search_ticket();
        else if (choice == 2) booking_history();
        else if (choice == 3) modify_ticket();
        else printf("Returning to main menu.\n");
        if (choice != 4) pause_screen();
    } while (choice != 4);
}
