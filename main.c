#include "railway.h"

int main(void) {
    int choice;
    initialize_data();
    load_bookings();

    printf("============================================\n");
    printf("       BULLET TRAIN TICKET BOOKING SYSTEM\n");
    printf("============================================\n");

    do {
        printf("\nMAIN MENU\n");
        printf("1. Train & Route Module\n");
        printf("2. Passenger & Booking Module\n");
        printf("3. Ticket & PNR Module\n");
        printf("4. Cancellation & Admin Module\n");
        printf("5. Exit\n");
        choice=read_int("Enter your choice: ",1,5);

        switch(choice) {
            case 1: train_module(); break;
            case 2: booking_module(); break;
            case 3: ticket_module(); break;
            case 4: admin_module(); break;
            case 5: save_bookings(); printf("Thank you for using the system!\n"); break;
        }
    } while(choice!=5);
    return 0;
}
