#ifndef RAILWAY_H
#define RAILWAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define TOTAL_STATIONS 15
#define TOTAL_TRAINS 6
#define MAX_BOOKINGS 5000
#define MAX_NAME 60
#define MAX_MOBILE 16
#define MAX_DATE 11
#define MAX_PNR 12
#define DATA_FILE "bookings.dat"
#define EXECUTIVE_SEATS 200
#define ECONOMIC_SEATS 600
#define TOTAL_SEATS (EXECUTIVE_SEATS + ECONOMIC_SEATS)
typedef struct { char name[30]; char arrival[12]; char departure[12]; } Station;
typedef struct { int id; char name[50]; int direction; char departure[12]; } Train;
typedef struct {
 char pnr[MAX_PNR]; char passenger_name[MAX_NAME]; int age; char gender[20]; char mobile[MAX_MOBILE];
 int train_id; int source_index; int destination_index; char journey_date[MAX_DATE];
 char travel_class[16]; int seat_number; double distance_km; double fare; int active;
} Booking;
extern Station stations[TOTAL_STATIONS];
extern Train trains[TOTAL_TRAINS];
extern Booking bookings[MAX_BOOKINGS];
extern int booking_count;
extern double executive_rate, economic_rate;
/* common utilities and persistent data */
void initialize_data(void); void load_bookings(void); void save_bookings(void);
void clear_input_buffer(void); void read_line(const char *, char *, int);
int read_int(const char *, int, int); double read_double(const char *, double, double); void pause_screen(void);
int date_is_valid(const char *); int valid_future_date(const char *);
/* Module 1: train and route */
void train_module(void); int find_train_by_id(int); double calculate_distance(int,int);
void display_all_stations(void); void display_all_trains(void); void search_trains(void); void display_route(int,int);
/* Module 2: passenger and booking */
void booking_module(void); int count_available_seats(int,const char *,const char *);
int find_available_seat(int,const char *,const char *); double calculate_fare(int,int,const char *);
int validate_route_for_direction(int,int,int);
/* Module 3: ticket and PNR */
void ticket_module(void); int find_booking_by_pnr(const char *); void generate_pnr(char *); void print_booking(const Booking *);
void search_ticket(void); void booking_history(void); void modify_ticket(void);
/* Module 4: cancellation and administration */
void admin_module(void); int admin_login(void); void cancel_ticket(void); void show_all_records(void);
void update_fares(void); void booking_summary(void); void display_admin_menu(void);
#endif
