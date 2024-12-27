public abstract class Vehicle {
    private String vehicleId;
    private String model;
    private double baseRentalRate;
    private boolean isAvailable;

    // Constructor
    public Vehicle(String vehicleId, String model, double baseRentalRate) {
        if (vehicleId == null || vehicleId.trim().isEmpty()) {
            throw new IllegalArgumentException("Vehicle ID cannot be null or empty.");
        }
        if (model == null || model.trim().isEmpty()) {
            throw new IllegalArgumentException("Model cannot be null or empty.");
        }
        if (baseRentalRate <= 0) {
            throw new IllegalArgumentException("Base rental rate must be greater than zero.");
        }

        this.vehicleId = vehicleId;
        this.model = model;
        this.baseRentalRate = baseRentalRate;
        this.isAvailable = true; // Default availability
    }

    // Getter and Setter for vehicleId
    public String getVehicleId() {
        return vehicleId;
    }

    public void setVehicleId(String vehicleId) {
        if (vehicleId == null || vehicleId.trim().isEmpty()) {
            throw new IllegalArgumentException("Vehicle ID cannot be null or empty.");
        }
        this.vehicleId = vehicleId;
    }

    // Getter and Setter for model
    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        if (model == null || model.trim().isEmpty()) {
            throw new IllegalArgumentException("Model cannot be null or empty.");
        }
        this.model = model;
    }

    // Getter and Setter for baseRentalRate
    public double getBaseRentalRate() {
        return baseRentalRate;
    }

    public void setBaseRentalRate(double baseRentalRate) {
        if (baseRentalRate <= 0) {
            throw new IllegalArgumentException("Base rental rate must be greater than zero.");
        }
        this.baseRentalRate = baseRentalRate;
    }

    // Getter and Setter for isAvailable
    public boolean isAvailable() {
        return isAvailable;
    }

    public void setAvailable(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    // Abstract methods
    public abstract double calculateRentalCost(int days);
    public abstract boolean isAvailableForRental();
}

    }

    // Getters and Setters
    public String getVehicleId() {
        return vehicleId;
    }

    public void setVehicleId(String vehicleId) {
        this.vehicleId = vehicleId;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public double getBaseRentalRate() {
        return baseRentalRate;
    }

    public void setBaseRentalRate(double baseRentalRate) {
        if(baseRentalRate > 0) {
            this.baseRentalRate = baseRentalRate;
        } else {
            throw new IllegalArgumentException("Rental rate must be positive.");
        }
    }

    public boolean isAvailable() {
        return isAvailable;
    }

    public void setAvailable(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    // Abstract methods
    public abstract double calculateRentalCost(int days);
    public abstract boolean isAvailableForRental();
}
// Car class
public class Car extends Vehicle {
    private boolean hasSunroof;

    public Car(String vehicleId, String model, double baseRentalRate, boolean hasSunroof) {
        super(vehicleId, model, baseRentalRate);
        this.hasSunroof = hasSunroof;
    }

    @Override
    public double calculateRentalCost(int days) {
        return getBaseRentalRate() * days;
    }

    @Override
    public boolean isAvailableForRental() {
        return isAvailable();
    }

    public boolean hasSunroof() {
        return hasSunroof;
    }
}

// Motorcycle class
public class Motorcycle extends Vehicle {
    private boolean hasSidecar;

    public Motorcycle(String vehicleId, String model, double baseRentalRate, boolean hasSidecar) {
        super(vehicleId, model, baseRentalRate);
        this.hasSidecar = hasSidecar;
    }

    @Override
    public double calculateRentalCost(int days) {
        return getBaseRentalRate() * days * 0.8; // Motorcycle discount
    }

    @Override
    public boolean isAvailableForRental() {
        return isAvailable();
    }

    public boolean hasSidecar() {
        return hasSidecar;
    }
}

// Truck class
public class Truck extends Vehicle {
    private double loadCapacity;

    public Truck(String vehicleId, String model, double baseRentalRate, double loadCapacity) {
        super(vehicleId, model, baseRentalRate);
        this.loadCapacity = loadCapacity;
    }

    @Override
    public double calculateRentalCost(int days) {
        return getBaseRentalRate() * days * 1.2; // Truck surcharge
    }

    @Override
    public boolean isAvailableForRental() {
        return isAvailable();
    }

    public double getLoadCapacity() {
        return loadCapacity;
    }
}
public interface Rentable {
    void rent(Customer customer, int days);
    void returnVehicle();
}
import java.util.ArrayList;
import java.util.List;

public class Customer {
    private String customerId;
    private String name;
    private List<Vehicle> currentRentals;

    public Customer(String customerId, String name) {
        this.customerId = customerId;
        this.name = name;
        this.currentRentals = new ArrayList<>();
    }

    public String getCustomerId() {
        return customerId;
    }

    public String getName() {
        return name;
    }

    public List<Vehicle> getCurrentRentals() {
        return currentRentals;
    }

    public void addRental(Vehicle vehicle) {
        currentRentals.add(vehicle);
    }

    public void returnRental(Vehicle vehicle) {
        currentRentals.remove(vehicle);
    }
}
import java.util.HashMap;
import java.util.Map;

public class RentalAgency {
    private String name;
    private Map<String, Vehicle> fleet;

    public RentalAgency(String name) {
        this.name = name;
        this.fleet = new HashMap<>();
    }

    public void addVehicle(Vehicle vehicle) {
        fleet.put(vehicle.getVehicleId(), vehicle);
    }

    public void removeVehicle(String vehicleId) {
        fleet.remove(vehicleId);
    }

    public Vehicle getVehicle(String vehicleId) {
        return fleet.get(vehicleId);
    }

    public void rentVehicle(Customer customer, String vehicleId, int days) {
        Vehicle vehicle = fleet.get(vehicleId);
        if (vehicle != null && vehicle.isAvailableForRental()) {
            customer.addRental(vehicle);
            vehicle.setAvailable(false); // Mark as rented
            System.out.println(customer.getName() + " rented " + vehicle.getModel() + " for " + days + " days.");
        } else {
            System.out.println("Vehicle is not available.");
        }
    }

    public void returnVehicle(Customer customer, Vehicle vehicle) {
        customer.returnRental(vehicle);
        vehicle.setAvailable(true); // Mark as returned
        System.out.println(vehicle.getModel() + " has been returned by " + customer.getName());
    }

    public void generateReport() {
        System.out.println("Rental Agency Fleet Report:");
        for (Vehicle vehicle : fleet.values()) {
            System.out.println(vehicle.getModel() + " - Available: " + vehicle.isAvailable());
        }
    }
}
public class RentalTransaction {
    private Vehicle vehicle;
    private Customer customer;
    private int rentalDays;
    private double rentalCost;

    public RentalTransaction(Vehicle vehicle, Customer customer, int rentalDays) {
        this.vehicle = vehicle;
        this.customer = customer;
        this.rentalDays = rentalDays;
        this.rentalCost = vehicle.calculateRentalCost(rentalDays);
    }

    public double getRentalCost() {
        return rentalCost;
    }

    public void printReceipt() {
        System.out.println("Rental Receipt:");
        System.out.println("Customer: " + customer.getName());
        System.out.println("Vehicle: " + vehicle.getModel());
        System.out.println("Rental Days: " + rentalDays);
        System.out.println("Total Cost: $" + rentalCost);
    }
}
public class Main {
    public static void main(String[] args) {
        // Create Rental Agency
        RentalAgency agency = new RentalAgency("Best Rentals");

        // Create Vehicles
        Vehicle car = new Car("V1", "Sedan", 30.0, true);
        Vehicle bike = new Motorcycle("V2", "Sportbike", 20.0, false);
        Vehicle truck = new Truck("V3", "Pickup", 50.0, 1000.0);

        // Add vehicles to fleet
        agency.addVehicle(car);
        agency.addVehicle(bike);
        agency.addVehicle(truck);

        // Create Customer
        Customer customer = new Customer("C1", "John Doe");

        // Rent Vehicle
        agency.rentVehicle(customer, "V1", 3);

        // Generate Rental Report
        agency.generateReport();

        // Return Vehicle
        agency.returnVehicle(customer, car);

        // Generate Rental Report again
        agency.generateReport();
    }
}

