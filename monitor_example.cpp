#include <Windows.h>
#include <iostream>
#include <highlevelmonitorconfigurationapi.h>

#pragma comment(lib, "Dxva2.lib")

int main() {
    HMONITOR virtual_monitor = MonitorFromWindow(GetForegroundWindow(), MONITOR_DEFAULTTOPRIMARY);

    DWORD monitors_arr_size;
    LPPHYSICAL_MONITOR monitors_arr = NULL;

    if (GetNumberOfPhysicalMonitorsFromHMONITOR(virtual_monitor, &monitors_arr_size)) {
        // Allocate the array of PHYSICAL_MONITOR structures.
        monitors_arr = (LPPHYSICAL_MONITOR) malloc(monitors_arr_size * sizeof(PHYSICAL_MONITOR));

        if (monitors_arr != NULL) {
            GetPhysicalMonitorsFromHMONITOR(virtual_monitor, monitors_arr_size, monitors_arr);

            // Get first monitor
            HANDLE physical_monitor = monitors_arr[0].hPhysicalMonitor;
            
            // Now we can interface with the monitor
            DWORD max_brightness;
            DWORD min_brightness;
            DWORD cur_brightness;
                
            GetMonitorBrightness(physical_monitor, &min_brightness, &cur_brightness, &max_brightness);
            printf("Max: %lu, Min: %lu, Cur: %lu\n", max_brightness, min_brightness, cur_brightness);

            system("pause");

            SetMonitorBrightness(physical_monitor, max_brightness);

            // Close the monitor handles.
            DestroyPhysicalMonitors(monitors_arr_size, monitors_arr);

            // Free the array.
            free(monitors_arr);
        }
    }
}