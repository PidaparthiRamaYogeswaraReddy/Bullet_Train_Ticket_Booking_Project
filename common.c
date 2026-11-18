#include "railway.h"

/* Shared storage used by all four modules. */
Booking bookings[MAX_BOOKINGS];
int booking_count = 0;
double executive_rate = 13.50;
double economic_rate = 7.50;

void initialize_data(void) {
    int i;
    for (i = 0; i < MAX_BOOKINGS; i++) bookings[i].active = 0;
}

void load_bookings(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) return;
    if (fread(&booking_count, sizeof(int), 1, fp) != 1) booking_count = 0;
    if (booking_count < 0 || booking_count > MAX_BOOKINGS) booking_count = 0;
    if (booking_count > 0 && fread(bookings, sizeof(Booking), (size_t)booking_count, fp) != (size_t)booking_count)
        booking_count = 0;
    fclose(fp);
}

void save_bookings(void) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) { printf("Warning: Could not save booking data.\n"); return; }
    fwrite(&booking_count, sizeof(int), 1, fp);
    fwrite(bookings, sizeof(Booking), (size_t)booking_count, fp);
    fclose(fp);
}

void clear_input_buffer(void) { int ch; while ((ch = getchar()) != '\n' && ch != EOF) {} }

void read_line(const char *prompt, char *buffer, int size) {
    int len;
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) { buffer[0] = '\0'; return; }
    len = (int)strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    else clear_input_buffer();
}

int read_int(const char *prompt, int min, int max) {
    char line[80], extra; int value;
    while (1) {
        read_line(prompt, line, sizeof(line));
        if (sscanf(line, "%d %c", &value, &extra) == 1 && value >= min && value <= max) return value;
        printf("Please enter a number from %d to %d.\n", min, max);
    }
}

double read_double(const char *prompt, double min, double max) {
    char line[80], extra; double value;
    while (1) {
        read_line(prompt, line, sizeof(line));
        if (sscanf(line, "%lf %c", &value, &extra) == 1 && value >= min && value <= max) return value;
        printf("Please enter a valid value from %.2f to %.2f.\n", min, max);
    }
}

int date_is_valid(const char *date) {
    int d, m, y; struct tm t; char extra;
    if (sscanf(date, "%2d-%2d-%4d%c", &d, &m, &y, &extra) != 3) return 0;
    if (y < 2024 || m < 1 || m > 12 || d < 1 || d > 31) return 0;
    memset(&t, 0, sizeof(t)); t.tm_mday = d; t.tm_mon = m - 1; t.tm_year = y - 1900; t.tm_hour = 12;
    if (mktime(&t) == (time_t)-1) return 0;
    return t.tm_mday == d && t.tm_mon == m - 1 && t.tm_year == y - 1900;
}

int valid_future_date(const char *date) {
    int d, m, y; struct tm trip, today; time_t now;
    if (!date_is_valid(date)) return 0;
    sscanf(date, "%2d-%2d-%4d", &d, &m, &y);
    memset(&trip, 0, sizeof(trip)); trip.tm_mday = d; trip.tm_mon = m - 1; trip.tm_year = y - 1900; trip.tm_hour = 12;
    now = time(NULL); today = *localtime(&now); today.tm_hour = 0; today.tm_min = 0; today.tm_sec = 0;
    return difftime(mktime(&trip), mktime(&today)) >= 0;
}

void pause_screen(void) { char temp[8]; read_line("\nPress Enter to continue...", temp, sizeof(temp)); }
