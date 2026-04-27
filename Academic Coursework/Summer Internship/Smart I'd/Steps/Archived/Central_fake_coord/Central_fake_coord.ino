#include <WiFi.h>
#include <map>
#include <vector>
#include <math.h> // Include the math library for trilateration

// Define a structure to represent a 2D point
typedef struct {
    float x;
    float y;
} Point;

const char* ssid = "Dark Matter";
const char* password = "omdinesh";
const uint16_t port = 80; // Port number to receive data on

IPAddress staticIP(192, 168, 137, 200); // Change to your desired static IP address
IPAddress gateway(192, 168, 137, 1);     // Change to your router's IP address
IPAddress subnet(255, 255, 255, 0);      // Change to your subnet mask
IPAddress dns(8, 8, 8, 8);               // Change to your DNS server's IP address

WiFiServer server(port);
WiFiClient client;

std::map<String, std::vector<int>> rssiMap; // Map to store RSSI values for each address
int beaconCounter = 0;                      // Counter to track the number of received data from all beacons

// Define beacon positions (either relative or actual distances)
Point beaconPositions[] = {
    {0, 0},    // Beacon 1
    {50, 100}, // Beacon 2
    {100, 0}   // Beacon 3
};

// Function to perform trilateration and calculate the device position
Point trilaterate(Point beaconPositions[], float distances[], int numBeacons) {
    // Define matrices and vectors for the linear least squares solution
    float A[2 * numBeacons][2] = {0}; // 2 * numBeacons rows, 2 columns
    float b[2 * numBeacons] = {0};    // 2 * numBeacons elements
    float x, y;

    // Populate matrices A and vector b
    for (int i = 0; i < numBeacons; i++) {
        float d2 = distances[i] * distances[i];
        A[i][0] = 2 * beaconPositions[i].x;
        A[i + numBeacons][1] = 2 * beaconPositions[i].y;
        b[i] = d2 - beaconPositions[i].x * beaconPositions[i].x - beaconPositions[i].y * beaconPositions[i].y;
        b[i + numBeacons] = d2 - beaconPositions[i].x * beaconPositions[i].x - beaconPositions[i].y * beaconPositions[i].y;
    }

    // Solve the linear least squares problem
    float det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    if (fabs(det) < 0.0001) {
        // Matrix is singular, unable to solve
        x = y = 0.0; // Default to origin
    } else {
        x = (A[1][1] * b[0] - A[0][1] * b[numBeacons]) / det;
        y = (A[0][0] * b[numBeacons] - A[1][0] * b[0]) / det;
    }

    // Return the device position
    Point devicePosition = {x, y};
    return devicePosition;
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Connecting to WiFi...");

    if (!WiFi.config(staticIP, gateway, subnet, dns)){
        Serial.println("FAILED to configure static IP!");
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void printRssiMap() {
    Serial.println("RSSI for each address:");
    for (auto& entry : rssiMap) {
        Serial.print("Address: ");
        Serial.print(entry.first);
        Serial.print(", RSSI values: ");
        for (int rssi : entry.second) {
            Serial.print(rssi);
            Serial.print(" ");
        }

        // Calculate device position using trilateration
        float distances[] = { entry.second[0], entry.second[1], entry.second[2] }; // RSSI values for each beacon
        Point devicePosition = trilaterate(beaconPositions, distances, sizeof(distances) / sizeof(distances[0]));
        
        // Print device position
        Serial.print(", Device Position: (");
        Serial.print(devicePosition.x);
        Serial.print(", ");
        Serial.print(devicePosition.y);
        Serial.println(")");
    }
}

void loop() {
    client = server.available();

    if (client) {
        String receivedData = ""; // Initialize variable to accumulate received data

        unsigned long startTime = millis(); // Get the start time

        while (client.connected() && (millis() - startTime < 5000)) {
            if (client.available()) {
                String data = client.readStringUntil('\n');
                receivedData += data + "; "; // Accumulate the received data
            }
        }

        Serial.println("Received data: [" + receivedData.substring(0, receivedData.length() - 2) + "]");

        // Split received data into individual records
        int startPos = 0;
        int endPos = 0;
        while ((endPos = receivedData.indexOf(';', startPos)) != -1) {
            String record = receivedData.substring(startPos, endPos);
            if (record.length() > 0) {
                int beaconNum = record.charAt(2) - '0'; // Extract beacon number
                int firstCommaPos = record.indexOf(',');
                String address = record.substring(firstCommaPos + 2, firstCommaPos + 14);
                int rssi = record.substring(record.lastIndexOf(',') + 2).toInt();
                if (rssiMap.find(address) == rssiMap.end()) {
                    // Address not found in the map, initialize with zeros
                    rssiMap[address] = std::vector<int>(3, 0);
                }
                rssiMap[address][beaconNum - 1] = rssi; // Store RSSI value for the address and beacon
            }
            startPos = endPos + 2;
        }

        beaconCounter++;

        if (beaconCounter >= 3) {
            printRssiMap();
            rssiMap.clear(); // Clear the RSSI map
            beaconCounter = 0;
        }

        client.stop();
    }
}
