#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* device type constants*/
#define TEMPERATURE 0
#define PRESSURE    1
#define BATTERY     2

struct Device {
    char name[30];
    int type;
    union {
        float temperature;
        int   pressure;
        float voltage;
    } reading;
};

/* Callback for devices  */
void temperature_monitor(struct Device *dev) {
    float t = dev->reading.temperature;
    printf("  [TEMP]     %-20s %.1f C  -->  ", dev->name, t);
    if (t > 50)
        printf("OVERHEATING!\n");
    else if (t > 30)
        printf("High - monitor closely\n");
    else if (t >= 0)
        printf("Normal\n");
    else
        printf("Below freezing\n");
}
void pressure_monitor(struct Device *dev) {
    int p = dev->reading.pressure;
    printf("  [PRESSURE] %-20s %d hPa  -->  ", dev->name, p);
    if (p < 900)
        printf("Very low pressure\n");
    else if (p < 1013)
        printf("Low pressure\n");
    else if (p <= 1030)
        printf("Normal\n");
    else
        printf("High pressure\n");
}
void battery_monitor(struct Device *dev) {
    float v = dev->reading.voltage;
    printf("  [BATTERY]  %-20s %.2f V  -->  ", dev->name, v);
    if (v < 3.0)
        printf("CRITICAL - replace now!\n");
    else if (v < 3.6)
        printf("Low\n");
    else if (v <= 4.1)
        printf("Normal\n");
    else
        printf("Fully charged\n");
}

void fault_detector(struct Device *dev) {
    int fault = 0;
    if (dev->type == TEMPERATURE && (dev->reading.temperature > 50 || dev->reading.temperature < -10)) {
        fault = 1;
    } else if (dev->type == PRESSURE && (dev->reading.pressure < 900 || dev->reading.pressure > 1050)) {
        fault = 1;
    } else if (dev->type == BATTERY && dev->reading.voltage < 3.0) {
        fault = 1;
    }

    if (fault) {
        printf("  ** FAULT DETECTED on device: %s **\n", dev->name);
    }
}

/* function pointer*/
void process_device(struct Device *dev, void (*callback)(struct Device *)) {
    callback(dev);
}


void random_reading(struct Device *dev) {
    if (dev->type == TEMPERATURE) {
        dev->reading.temperature = -20 + (rand() % 90);
    } else if (dev->type == PRESSURE) {
        dev->reading.pressure = 870 + (rand() % 190);
    } else {
        dev->reading.voltage = 2.5 + (rand() % 20) / 10.0;
    }
}

int main() {
    srand(time(NULL));

    printf("================================\n");
    printf("  Device Monitoring Simulator\n");
    printf("  Student ID: [YOUR_STUDENT_ID]\n");
    printf("  Custom CB: Fault Detector\n");
    printf("================================\n\n");

   
    struct Device catalogue[9] = {
        {"TempSensor_A",  TEMPERATURE, {0}},
        {"TempSensor_B",  TEMPERATURE, {0}},
        {"TempSensor_C",  TEMPERATURE, {0}},
        {"PressGauge_X",  PRESSURE,    {0}},
        {"PressGauge_Y",  PRESSURE,    {0}},
        {"PressGauge_Z",  PRESSURE,    {0}},
        {"Battery_1",     BATTERY,     {0}},
        {"Battery_2",     BATTERY,     {0}},
        {"Battery_3",     BATTERY,     {0}}
    };

    void (*callbacks[3])(struct Device*) = {
        temperature_monitor,
        pressure_monitor,
        battery_monitor
    };

    int num = 10;
    struct Device *readings = malloc(num * sizeof(struct Device));
    printf("Readings array at memory address: %p\n\n", (void*)readings);

    
    int i;
    for (i = 0; i < num; i++) {
        int idx = rand() % 9;
        *(readings + i) = catalogue[idx];
        random_reading(readings + i);
    }

    
    printf("--- Simulating %d Device Readings ---\n", num);
    for (i = 0; i < num; i++) {
        struct Device *d = readings + i;
        printf("%2d. ", i + 1);
        process_device(d, callbacks[d->type]);
        process_device(d, fault_detector);
    }

    free(readings);
    printf("\nSimulation complete.\n");
    return 0;
}