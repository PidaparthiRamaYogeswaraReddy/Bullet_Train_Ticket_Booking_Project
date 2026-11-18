#include "railway.h"

#define ADMIN_ID "admin"
#define ADMIN_PASSWORD "1234"

/* MODULE 4: CANCELLATION AND ADMINISTRATION */

int admin_login(void) {
    char id[30], password[40];
    int attempt;
    for (attempt = 1; attempt <= 3; attempt++) {
        read_line("Admin ID: ", id, sizeof(id));
        read_line("Admin password: ", password, sizeof(password));
        if (strcmp(id, ADMIN_ID) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("Login successful. Welcome, administrator.\n");
            return 1;
        }
        printf("Incorrect login. Attempts remaining: %d\n", 3 - attempt);
    }
    printf("Admin access denied.\n");
    return 0;
}

static int find_any_booking(const char *pnr) {
    int i;
    for (i = 0; i < booking_count; i++)
        if (strcmp(bookings[i].pnr, pnr) == 0) return i;
    return -1;
}

void cancel_ticket(void) {
    char pnr[MAX_PNR], confirm[8];
    int index;
    double refund;
    read_line("Enter PNR to cancel: ", pnr, sizeof(pnr));
    index = find_any_booking(pnr);
    if (index < 0) { printf("Booking not found.\n"); return; }
    if (!bookings[index].active) { printf("Ticket is already cancelled.\n"); return; }
    printf("Passenger: %s\nTrain ID: %d\nDate: %s\nSeat: %d\nFare: Rs. %.2f\n",
           bookings[index].passenger_name, bookings[index].train_id,
           bookings[index].journey_date, bookings[index].seat_number, bookings[index].fare);
    refund = bookings[index].fare * 0.80;
    printf("Demonstration refund (80%%): Rs. %.2f\n", refund);
    read_line("Confirm cancellation? (YES/NO): ", confirm, sizeof(confirm));
    if (strcmp(confirm, "YES") != 0 && strcmp(confirm, "yes") != 0) {
        printf("Cancelled request withdrawn. Ticket remains active.\n"); return;
    }
    bookings[index].active = 0;
    save_bookings();
    printf("Ticket cancelled. Seat %d is available again. Refund: Rs. %.2f\n",
           bookings[index].seat_number, refund);
}

void show_all_records(void) {
    int i, count = 0;
    for (i = 0; i < booking_count; i++)
        if (bookings[i].active) { print_booking(&bookings[i]); count++; }
    if (!count) printf("No active bookings.\n");
    else printf("Active booking records: %d\n", count);
}

static void show_cancelled_records(void) {
    int i, count = 0;
    printf("\n========== CANCELLED TICKETS ==========\n");
    for (i = 0; i < booking_count; i++) {
        if (!bookings[i].active) {
            printf("%s | %s | %s | Rs. %.2f\n", bookings[i].pnr,
                   bookings[i].passenger_name, bookings[i].journey_date, bookings[i].fare);
            count++;
        }
    }
    if (!count) printf("No cancelled tickets found.\n");
    else printf("Cancelled records: %d\n", count);
}

void booking_summary(void) {
    int i, active = 0, cancelled = 0;
    double revenue = 0, cancelled_fare = 0;
    for (i = 0; i < booking_count; i++) {
        if (bookings[i].active) { active++; revenue += bookings[i].fare; }
        else { cancelled++; cancelled_fare += bookings[i].fare; }
    }
    printf("\n========== BOOKING SUMMARY ==========\n");
    printf("Total records: %d\nActive: %d\nCancelled: %d\n", booking_count, active, cancelled);
    printf("Active fare total: Rs. %.2f\nCancelled fare value: Rs. %.2f\n", revenue, cancelled_fare);
    if (booking_count) printf("Cancellation percentage: %.2f%%\n", cancelled * 100.0 / booking_count);
}

void update_fares(void) {
    double old_ex = executive_rate, old_ec = economic_rate;
    printf("Current Executive rate: Rs. %.2f/km\n", old_ex);
    printf("Current Economic rate : Rs. %.2f/km\n", old_ec);
    executive_rate = read_double("New Executive rate per km: ", 0.01, 10000);
    economic_rate = read_double("New Economic rate per km: ", 0.01, 10000);
    if (executive_rate < economic_rate) printf("Warning: Executive rate is below Economic rate.\n");
    printf("Fare rates updated for future bookings.\n");
    printf("Executive: %.2f -> %.2f\nEconomic: %.2f -> %.2f\n",
           old_ex, executive_rate, old_ec, economic_rate);
}

static void search_admin_records(void) {
    int id, i, found = 0;
    char date[MAX_DATE];
    id = read_int("Enter train ID (1-6): ", 1, TOTAL_TRAINS);
    read_line("Enter journey date (DD-MM-YYYY): ", date, sizeof(date));
    if (!date_is_valid(date)) { printf("Invalid date format.\n"); return; }
    for (i = 0; i < booking_count; i++) {
        if (bookings[i].train_id == id && strcmp(bookings[i].journey_date, date) == 0) {
            printf("%s | %s | Seat %d | %s\n", bookings[i].pnr,
                   bookings[i].passenger_name, bookings[i].seat_number,
                   bookings[i].active ? "ACTIVE" : "CANCELLED");
            found++;
        }
    }
    if (!found) printf("No matching records.\n");
    else printf("Matching records: %d\n", found);
}

static void export_report(void) {
    FILE *file = fopen("booking_report.csv", "w");
    int i;
    if (!file) { printf("Could not create report file.\n"); return; }
    fprintf(file, "PNR,Passenger,Train ID,Date,Class,Seat,Fare,Status\n");
    for (i = 0; i < booking_count; i++)
        fprintf(file, "%s,\"%s\",%d,%s,%s,%d,%.2f,%s\n", bookings[i].pnr,
                bookings[i].passenger_name, bookings[i].train_id, bookings[i].journey_date,
                bookings[i].travel_class, bookings[i].seat_number, bookings[i].fare,
                bookings[i].active ? "ACTIVE" : "CANCELLED");
    fclose(file);
    printf("Report saved as booking_report.csv.\n");
}

void display_admin_menu(void) {
    int choice;
    do {
        printf("\n========== ADMIN CONTROL PANEL ==========\n");
        printf("1. View active bookings\n2. Update fare rates\n3. Booking summary\n");
        printf("4. View cancelled bookings\n5. Search by train and date\n6. Export CSV report\n7. Logout\n");
        choice = read_int("Choose: ", 1, 7);
        switch (choice) {
            case 1: show_all_records(); break;
            case 2: update_fares(); break;
            case 3: booking_summary(); break;
            case 4: show_cancelled_records(); break;
            case 5: search_admin_records(); break;
            case 6: export_report(); break;
            case 7: printf("Admin logged out.\n"); break;
        }
        if (choice != 7) pause_screen();
    } while (choice != 7);
}

void admin_module(void) {
    int choice;
    do {
        printf("\n========== MODULE 4: CANCELLATION & ADMIN ==========\n");
        printf("1. Cancel ticket using PNR\n2. Admin login\n3. Back to main menu\n");
        choice = read_int("Choose: ", 1, 3);
        if (choice == 1) { cancel_ticket(); pause_screen(); }
        else if (choice == 2 && admin_login()) display_admin_menu();
    } while (choice != 3);
}
