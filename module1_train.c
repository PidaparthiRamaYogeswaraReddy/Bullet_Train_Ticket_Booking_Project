#include "railway.h"

/* Module 1 owns the train and station master data. */
Station stations[TOTAL_STATIONS] = {
 {"New Delhi","06:00 AM","06:00 AM"},{"Jaipur","06:44 AM","06:49 AM"},
 {"Ahmedabad","08:30 AM","08:35 AM"},{"Vadodara","08:54 AM","08:59 AM"},
 {"Surat","09:24 AM","09:29 AM"},{"Mumbai","10:13 AM","10:18 AM"},
 {"Pune","10:40 AM","10:45 AM"},{"Nagpur","12:42 PM","12:47 PM"},
 {"Raipur","01:36 PM","01:41 PM"},{"Kolkata","03:54 PM","03:59 PM"},
 {"Bhubaneswar","05:07 PM","05:12 PM"},{"Visakhapatnam","06:27 PM","06:32 PM"},
 {"Hyderabad","08:06 PM","08:11 PM"},{"Bengaluru","09:44 PM","09:49 PM"},
 {"Chennai","10:43 PM","--"}
};
Train trains[TOTAL_TRAINS] = {
 {1,"Bullet Express - Morning",0,"06:00 AM"},{2,"Bullet Express - Midday",0,"09:00 AM"},
 {3,"Bullet Express - Afternoon",0,"12:00 PM"},{4,"Bullet Express - Morning",1,"06:00 AM"},
 {5,"Bullet Express - Midday",1,"09:00 AM"},{6,"Bullet Express - Afternoon",1,"12:00 PM"}
};
static const double segment_km[TOTAL_STATIONS - 1] = {300,550,110,160,280,150,700,300,700,440,450,620,570,350};

int find_train_by_id(int id) {
    int i; for (i = 0; i < TOTAL_TRAINS; i++) if (trains[i].id == id) return i;
    return -1;
}

double calculate_distance(int source, int destination) {
    int i, low, high; double total = 0;
    if (source == destination) return 0;
    low = source < destination ? source : destination; high = source < destination ? destination : source;
    for (i = low; i < high; i++) total += segment_km[i];
    return total;
}

void display_all_stations(void) {
    int i;
    printf("\n%-4s %-20s %-14s %s\n", "No.", "Station", "Arrival", "Departure");
    for (i = 0; i < TOTAL_STATIONS; i++)
        printf("%-4d %-20s %-14s %s\n", i + 1, stations[i].name, stations[i].arrival, stations[i].departure);
    printf("\nThis is the supplied Delhi-to-Chennai sample timetable. Reverse timings are illustrative.\n");
}

void display_all_trains(void) {
    int i;
    printf("\n%-5s %-23s %-14s %s\n", "ID", "Direction", "Departure", "Train name");
    for (i = 0; i < TOTAL_TRAINS; i++)
        printf("%-5d %-23s %-14s %s\n", trains[i].id,
          trains[i].direction == 0 ? "Chennai -> Delhi" : "Delhi -> Chennai", trains[i].departure, trains[i].name);
}

int validate_route_for_direction(int direction, int source, int destination) {
    if (source < 0 || source >= TOTAL_STATIONS || destination < 0 || destination >= TOTAL_STATIONS || source == destination) return 0;
    if (direction == 0) return source > destination;
    return source < destination;
}

void display_route(int source, int destination) {
    int i, step = source < destination ? 1 : -1;
    printf("Route: ");
    for (i = source; ; i += step) { printf("%s", stations[i].name); if (i == destination) break; printf(" -> "); }
    printf("\nApproximate distance: %.0f km\n", calculate_distance(source, destination));
}

void search_trains(void) {
    int direction, i, source, destination, found = 0;
    printf("1. Chennai to Delhi\n2. Delhi to Chennai\n");
    direction = read_int("Select direction: ", 1, 2) - 1;
    printf("\nMatching trains:\n");
    for (i = 0; i < TOTAL_TRAINS; i++) if (trains[i].direction == direction) {
        printf("Train ID %d | %s | Departure %s\n", trains[i].id, trains[i].name, trains[i].departure); found++;
    }
    printf("Found %d trains.\n", found);
    display_all_stations();
    source = read_int("Source station number: ", 1, TOTAL_STATIONS) - 1;
    destination = read_int("Destination station number: ", 1, TOTAL_STATIONS) - 1;
    if (!validate_route_for_direction(direction, source, destination)) printf("Invalid route for selected direction.\n");
    else display_route(source, destination);
}

void train_module(void) {
    int choice;
    do {
        printf("\n========== MODULE 1: TRAIN & ROUTE ==========\n");
        printf("1. Display all stations and timetable\n2. Display all six trains\n3. Search trains and route\n4. Back to main menu\n");
        choice = read_int("Choose: ", 1, 4);
        if (choice == 1) display_all_stations();
        else if (choice == 2) display_all_trains();
        else if (choice == 3) search_trains();
        if (choice != 4) pause_screen();
    } while (choice != 4);
}
