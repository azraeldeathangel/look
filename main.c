#include <stdio.h>
#include <windows.h>

// Function to read and display the contents of a file
void readfile(const char *filename) {
    HANDLE filehandle;
    DWORD bytesread;
    char buffer[4096]; // Buffer to store file contents before printing

    // Open the file with read access
    filehandle = CreateFileA(
        filename,          // File name
        GENERIC_READ,      // Open for reading
        FILE_SHARE_READ,   // Allow other processes to read the file
        NULL,              // Default security attributes
        OPEN_EXISTING,     // Open only if the file exists
        FILE_ATTRIBUTE_NORMAL, // Normal file attributes
        NULL);             // No template file

    // Check if the file was opened successfully
    if (filehandle == INVALID_HANDLE_VALUE) {
        printf("Error opening file: %lu\n", GetLastError()); // Print error code
        return;
    }

    // Read the file in chunks and print to standard output
    while (ReadFile(filehandle, buffer, sizeof(buffer), &bytesread, NULL) && bytesread > 0) {
        fwrite(buffer, sizeof(char), bytesread, stdout); // Print contents to console
    }

    // Close the file handle after reading
    CloseHandle(filehandle);
}

int main(int argc, char const *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]); // Inform the user of correct usage
        return 1; // Exit with error code
    }

    readfile(argv[1]); // Call the function to read the file
    return 0; // Successful execution
}
