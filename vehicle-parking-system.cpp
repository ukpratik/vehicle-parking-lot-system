#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Vehicle{
    private:
        string VehicleType;
        string VehicleID;
        vector<pair<int,int>> location;

    public:
        Vehicle(){
        }
        Vehicle(string type, string id){
            VehicleType = type;
            VehicleID = id;
        }
        string getVehicleType(){
            return VehicleType;
        }
        string getID(){
            return VehicleID;
        }
        void setID(string id){
            VehicleID = id;
        }
        void setVehicleLocation(int i, int j){
            location.push_back(pair(i,j));
        }

        vector<pair<int,int>> getVehicleLocation(){
           return location;
        }
};

class Slot{
    private:
        bool is_occupied;
        Vehicle vehicle;

    
    public:
        Slot(string type, string id){
            is_occupied = true;
            vehicle = Vehicle(type, id);
        }

        Slot(Vehicle v){
            is_occupied = true;
            vehicle = v;
        }
        Slot(){
            is_occupied = false;
        }

        Vehicle getVehicle(){
            return vehicle;
        }

        bool isOccupied(){
            return this->is_occupied;
        }
        void fill(Vehicle vehicle){
            this->is_occupied = true;
            this->vehicle = vehicle;
        }
        void remove(){
            this->is_occupied = false;
            // delete this->vehicle;
        }
};

class ParkingLot{
    private:
        int length;
        int breadth;
        int TotalSize;
        int AvailableSize;
        vector<vector<Slot>> slots;

    public:
        ParkingLot(int length=10, int  breadth=10){
            this->length = length;
            this->breadth = breadth;
            this->TotalSize = length * breadth;
            // slots.resize(length, vector<int>(breadth,0));
            for(int i = 0; i < length; ++i){
                slots.push_back(vector<Slot>{});
                for(int j = 0; j < breadth; ++j){
                    slots[i].push_back(Slot());
                }
            }
        }

        void addVehicle(Vehicle vehicle){
            bool found;
            Slot new_slot = Slot(vehicle);
            if(vehicle.getVehicleType() == "2"){
                for(int i = 0; i < length; ++i){
                    for(int j = 0; j < breadth; ++j){
                        if(slots[i][j].isOccupied() == false){
                            slots[i][j] = new_slot;
                            vehicle.setVehicleLocation(i,j);
                            // delete new_slot;
                            // new_slot = NULL;
                            found = true;
                            return;
                        }
                    }
                    if(found) return;
                }
            }else if(vehicle.getVehicleType() == "4"){
                for(int i = 0; i < length; ++i){
                    for(int j = 0; j < breadth; ++j){
                        if(slots[i][j].isOccupied() == false){
                            if(i+1 < length && slots[i+1][j].isOccupied()==false){
                                slots[i][j] = new_slot;
                                // new_slot = Slot(vehicle);
                                slots[i+1][j] = new_slot;
                                vehicle.setVehicleLocation(i,j);
                                vehicle.setVehicleLocation(i+1,j);
                            }else if(j+1 < breadth && slots[i][j+1].isOccupied()==false){
                                slots[i][j] = new_slot;
                                // new_slot = Slot(vehicle);
                                slots[i][j+1] = new_slot;
                                vehicle.setVehicleLocation(i,j);
                                vehicle.setVehicleLocation(i,j+1);
                            }else if(j-1 < breadth && slots[i][j-1].isOccupied()==false){
                                slots[i][j] = new_slot;
                                // new_slot = Slot(vehicle);
                                slots[i][j-1] = new_slot;
                                vehicle.setVehicleLocation(i,j);
                                vehicle.setVehicleLocation(i,j-1);
                            }else if(i-1 < breadth && slots[i-1][j].isOccupied()==false){
                                slots[i][j] = new_slot;
                                // new_slot = Slot(vehicle);
                                slots[i-1][1] = new_slot;
                                vehicle.setVehicleLocation(i,j);
                                vehicle.setVehicleLocation(i-1,j);
                            }
                            return;
                        }
                    }
                }
            }
        }
        void removeVehicle(string vehicleID){
            for(int i = 0; i < length; ++i){
                for(int j = 0 ; j < breadth; ++j){
                    if(slots[i][j].getVehicle().getID() == vehicleID){
                        if(slots[i][j].getVehicle().getVehicleType() == "4"){
                            
                            vector<pair<int, int>> p;
                            p = slots[i][j].getVehicle().getVehicleLocation();
                            slots[p[0].first][p[0].second] = Slot();
                            slots[p[1].first][p[1].second] = Slot();
                            return;
                        }else if(slots[i][j].getVehicle().getVehicleType() == "2"){
                            
                            vector<pair<int, int>> p;
                            p = slots[i][j].getVehicle().getVehicleLocation();
                            slots[p[0].first][p[0].second] = Slot();
                            // slots[p[1].first][p[1].second] = Slot();
                            return;
                        }
                    }
                }
            }
        }
        void printLot(){
            cout << "******* Printing Lot *******\n";
            for(int i = 0; i < length; ++i){
                for(int j = 0 ; j < breadth; ++j){
                    Slot slt = slots[i][j];
                    if(slt.isOccupied()){
                        cout << slt.getVehicle().getID() << " \t";
                    }else{
                        cout << " 0 \t";
                    }
                }
                cout << " \n";
            }
            cout << "***************************\n";
        }
};

class ParkingSystem{
    private:
        int MaxParkingLots = 100;
        int CurrParkingLots;
        vector<ParkingLot> lots;

    public:
        ParkingSystem(){
            CurrParkingLots = 0;
        }

        
};

int main(){
    int l = 10;
    int b = 10;
    ParkingLot p1(l, b);
    p1.printLot();
    p1.addVehicle(Vehicle("2", "11"));
    p1.addVehicle(Vehicle("2", "13"));
    
    p1.printLot();
    
    p1.addVehicle(Vehicle("4", "15"));
    p1.addVehicle(Vehicle("2", "17"));

    p1.printLot();

    p1.addVehicle(Vehicle("4", "19"));
    p1.addVehicle(Vehicle("2", "20"));

    p1.printLot();
    return 0;
}