# User Manual

## Table of Contents
1. Getting Started
2. Environment Setup
3. Additional Dependencies
4. Running the Simulated Sensors
5. Using the Device Controller
6. FAQ

## 1. Getting Started
### What is the DistoY?
The DistoY is a cave surveying device aimed at providing cavers with a larger variety of functionality for surveying at a much lower cost than current products on the market. The DistoY will allow for taking distance measurements that can also record angles, track cardinal direction, and store data for later use. Furthermore, it will also be built to survive in the harsh conditions of caves, such as being dropped from heights, exposed to lots of dust, cold temperatures, and wetness or submersion in water.

### How can I try it?
Currently, the DistoY uses simulated sensors and a standalone program in order to simulate how the physical would work in the real world. You can try out this simulation by following this guide and setting up the sensor simulations and device controller on your own computer.

### System Requirements
To use run the DistoY simulation code, you must have access to a computer which either runs on a Linux, or can have software installed to emulate a Linux environment. Linux and Mac machines will work natively, and Windows machines will need additional software.

## 2. Environment Setup

### Linux & Mac Machines
If you have either a Mac or Linux machine, you can skip to the next section.

### Windows Machines
1. First you will need to install an Ubuntu (or any Linux) environment. I recommend going to the Windows Store and selecting 'Get' on the Ubuntu environment there:

![image](https://user-images.githubusercontent.com/33441174/232184294-9a1ea01b-30c0-4f0d-9a5f-05b3cf077489.png)

2. You will then need to clone this git repository into your Ubuntu environment by running the following command:

![image](https://user-images.githubusercontent.com/33441174/232184334-8a84ce0d-f9ef-411f-944a-eaf1236e1194.png)

## 3. Additional Dependencies
This projects relies on NumPy for the device controller, as this is able to handle the vector math needed to calculate heading. Because of this, please ensure that your Ubuntu/Linux Environment has a compatible version of NumPy with Python3. Here is the guide for installing [NumPy](https://numpy.org/install/).

## 4. Running the Simulated Sensors

### Navigating to the Code
Once your environment is setup, you simply access the code using the following command from your environment terminal:

![image](https://user-images.githubusercontent.com/33441174/232184457-df25aabd-6e8e-4512-9af4-f8579a124ebc.png)

### Starting Up the Inclinometer & Magnetometer
Both the inclinometer and magnetometer are simulated using the HWT905-TTL sensor in this current version of the DistoY. Therefore, we only need to startup a single simulation for the functionality of both the inclinometer and magnetometer.

1. First, navigate to the HWT905-TTL sensor simulation directory using the following command:

![image](https://user-images.githubusercontent.com/33441174/232184520-101d2e53-670f-420e-8a70-975061532074.png)

2. Next, we need to compile the simulation code so that the program can run using the following command:

![image](https://user-images.githubusercontent.com/33441174/232184562-7793f03a-c413-4201-93e5-f6b083ea86cb.png)

3. Finally, we can start the HWT905-TTL sensor simulation by running this final command:

![image](https://user-images.githubusercontent.com/33441174/232184598-92540d69-7893-4f09-9fac-5c73b76a2589.png)

### Starting Up the Laser Range Finder
For the laser range finder, this is simulated using the LRF60M-10PH sensor. For this simulation, we will follow a very similar set of instructions compared to the previous section.

1. First, navigate to the LRF60M-10PH sensor simulation directory using the following command: 

![image](https://user-images.githubusercontent.com/33441174/232184796-8e11fa6e-1970-426c-94bf-d77368ebb664.png)

2. Next, we need to compile the simulation code so that the program can run using the following command:

![image](https://user-images.githubusercontent.com/33441174/232184829-e2d616cd-c98f-4be3-b02a-cfa0c9442bf9.png)

3. Finally, we can start the LRG60M-10PH sensor simulation by running this final command:

![image](https://user-images.githubusercontent.com/33441174/232184850-0630eca3-77a3-4223-bfac-7381b07ba00b.png)

**Note: You must run a separate terminal instance for each sensor.**

## 5. Using the Device Controller

## Navigating to the Code
Similar to the sensors, we can navigate to the code for the device controller by running the following command:

![image](https://user-images.githubusercontent.com/33441174/232184973-8f726c5e-bd78-4e1f-8bb4-291920deeef4.png)

## Starting up the Device Controller
This device controller runs an interactive prompt that you can use to run the various commands of the DistoY. To start the program, simply run the following command:

![image](https://user-images.githubusercontent.com/33441174/232185042-92b0312d-bd89-428c-95d8-186fcf3e596e.png)

You should be prompted to enter a command. To learn more about the commands of the DistoY, simply type 'help' as your command:

![image](https://user-images.githubusercontent.com/33441174/232185084-cd73bc6e-e224-4ef7-b58b-cda83e68646b.png)

## Accessing Stored Data
After running the device controller for a while, you may wish to review your saved data. This data is stored as a .txt file, and can be accessed using any text editor of your choosing. I will show a simple way to view this data using nano. Just run the following command:

![image](https://user-images.githubusercontent.com/33441174/232185387-4e058343-40d7-4896-88f3-75937b9f49d7.png)

You should then be shown your file's data, I've provided my as an example:

![image](https://user-images.githubusercontent.com/33441174/232185412-5b9b1c85-8c06-481a-9f8a-cc90cff06841.png)

**Note: You must run a separate terminal instance for the device controller.**
  
## 6. FAQ


