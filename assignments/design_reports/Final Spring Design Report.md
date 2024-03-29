# Final Spring Report

## Table of Contents
1. [Project Description](#project-description)
2. [User Interface Specification](#user-interface-specification)
3. [Test Plan and Results](#test-plan-and-results)
4. [User Manual](#user-manual)
5. [Spring Final PPT Presentation](#spring-final-ppt-presentation)
6. [Final Expo Poster](#final-expo-poster)
7. [Assessments](#assessments)
     1. [Initial Self Assessment](#initial-self-assessment)
     2. [Final Self Assessment](#final-self-assessment)
9. [Summary of Hours and Justification](#summary-of-hours-and-justification)
10. [Summary of Expenses](#summary-of-expenses)
11. [Appendix](#appendix)

## Project Description

### Abstract
DistoY is a cave surveying device aimed at providing cavers with a larger variety of functionality for surveying at a much lower cost
than current products on the market. The DistoY will allow for taking distance measurements that can also record angles, track cardinal
direction, and store data for later use. Furthermore, it will also be built to survive in the harsh conditions of caves, such as being
dropped from heights, exposed to lots of dust, cold temperatures, and wetness or submersion in water.

### Description
The purpose of this project is to provide a cheaper and more reliable surveying device to cavers. The current solutions that exist are
either extremely expensive, lacking in features, or both. The aim of the DistoY is to create an API for commonly available sensors
that is able to deliver vital features, such as distance measurement, angle measurement, and cardinal direction tracking. It also
aims to allow for the storage of data for processing at a later date. Since this API will be publicly available and well-documented,
the goal is for future feature development that can either completed by myself or others in the caving community. This repository
provides the ability to interact with the chosen sensors as simulation programs, with the intention of being used to eventually
create a final physical design for this device.

## User Interface Specification

### Specification
This project has two main interfaces for the user to use. The first are the sensor logs, which allows the user to read what is happening
inside the simulated sensors in real-time. The second is the interactive device controller, which allows the user to issue commands to
the sensors simulations, save data, and calibrate the sensors. Each sensor, as well as the device controller, runs in its own
separate terminal. If you are unsure of how to setup and use these interfaces, please reference the [User Manual Section](#user-manual).

### Sensor Simulation Interface
![image](https://user-images.githubusercontent.com/33441174/232245942-838f3837-5545-4462-a2ec-cfe2ca384223.png)

### Device Controller Interface
![image](https://user-images.githubusercontent.com/33441174/232245986-540245a5-9020-4659-bb50-5d01a211270d.png)

## Test Plan and Results

### [Test Plan Link](https://github.com/DarkNomads/DistoY/blob/08a9a0296a9ed2ccbdb65ce45c902905b4630ff1/assignments/testing/Test_Plan.pdf)

### Testing Process Explanation
#### Unit Tests
Since all interprogram communiation is done through the use of reading and writing to files, all unit tests involving communication can
be tested by manually writing values into these files. This allows for individuals parts of the software to be tested without relying on
the functionality of others.

#### Integration Tests
Since integration tests are testing how parts of the software work with one another, this can simply be tested by running the appropriate
parts together, and observing that whatever data or action happens between them is consistent within the design specifications.

### Results
#### Sensor API (SA) Tests
* Laser Range Finder (SA1) - <strong> Passed </strong>
  1. Started up the LRF60M-10PH simulation.
  2. Manually typed command to take measurement into lrf60m_10ph.in.
  3. Observed an appropritate response in lrf60m_10ph.out.

* Inclinometer (SA2) - <strong> Passed </strong>
  1. Started up the HWT905-TTL simulation.
  2. Manually typed command to take angle measurement into hwt905_ttl.in.
  3. Observed an appropritate response in hwt905_ttl.out.

* Magnetometer (SA3) - <strong> Passed </strong>
  1. Started up the HWT905-TTL simulation.
  2. Manually typed commands to read the accelerometer and magnetic field into hwt905_ttl.in.
  3. Observed appropritate responses in hwt905_ttl.out.

#### Data Processor (DP) Tests
* Request Reading (DP1) - <strong> Passed </strong>
  1. Started up the LRF60M-10PH simulation.
  2. Started up the HWT905-TTL simulation.
  3. Started up the device controller program.
  4. Entered the 'data point' command into the device controller terminal.
  5. Observed an appropriate response in the device controller terminal.

* Data Formatting (DP2) - <strong> Passed </strong>
  1. Enabled debugging mode by adding a log statement in the data formatting routine.
  2. Added a dummy data point in the device controller program.
  3. Started up the device controller program.
  4. Entered the 'save' command into the device controller terminal.
  5. Observed the log statement has the appropriate JSON format.

* Data Storage (DP3) - <strong> Passed </strong>
  1. Added a dummy data point in the device controller program.
  2. Started up the device controller program.
  3. Entered the 'save' command into the device controller terminal.
  4. Observed the data was stored in data/saved_data.txt.

* Data Retrieval (DP4)
  * This test was deprecated, as being able to retrieve data from the SD card was no longer needed.

#### I/O Controller (IO) Tests
* Calculation Selection (IO1) - <strong> Passed </strong>
  1. Enabled debugging mode by adding log statements when selecting a command.
  2. Started up the device controller program.
  3. Ran each available command.
  4. Observed that each command corresponded to the appropriate log statement in the terminal.

* Data Received (IO2) - <strong> Passed </strong>
  1. Started up the LRF60M-10PH simulation.
  2. Started up the HWT905-TTL simulation.
  3. Started up the device controller program.
  4. Entered the 'measurement' command into the device controller terminal.
  5. Observed an appropriate response in the device controller terminal.

#### Physical Device (PD) Tests
* These tests were deprecated, as the physicaldevice was not finished.

## User Manual

### [User Manual Link](https://github.com/DarkNomads/DistoY/blob/2d846c7e0fa8cb2d2f5fdba46566bd595f8db8d8/user_docs/user_manual.md)

### User Manual FAQ
* Do I need to run multiple instances of the terminal for the simulations to work?
  * <strong> Yes - each sensor and the device controller need to be run on a separate instance. </strong>

* How are the sensor values generated?
  *  <strong> As of now, all of the sensor values are randomly generated within their specified value ranges. </strong>

* Can I run multiple instances of the sensor simulations?
  *  <strong> It is not recommended to run multiple versions of the sensor simulations, since they may interfere with data reads and writes. </strong>

* How can I stop the sensor simulations?
  *  <strong> Simply navigate to the terminal running the simulation, and press Crtl+C to end the simulation. </strong>

## Spring Final PPT Presentation

### [PPT Slidedeck Link](https://github.com/DarkNomads/DistoY/blob/2d846c7e0fa8cb2d2f5fdba46566bd595f8db8d8/assignments/presentations/DistoY%20Presentation%20-%20Spring%202023.pdf)

### [Presentation Link](https://youtu.be/2vx8ASrVzAI)

## Final Expo Poster

###  [High Resolution PDF Link](https://github.com/DarkNomads/DistoY/blob/2d846c7e0fa8cb2d2f5fdba46566bd595f8db8d8/assignments/expo_poster/ExpoPoster.pdf)

![image](https://user-images.githubusercontent.com/33441174/232244701-000df559-5d16-4fd4-8b22-728792aba8f7.png)

## Assessments

### Initial Self Assessment
During these first few months of working on the project, I have mainly focused on deciding on and ordering all the necessary physical components, as well as working on the Sensor API implementation for communicating with the sensors. Due to unforeseen issues with global electronic shortages, I had to push physical prototyping further out and began working on a mock-up API so that I could remain on schedule with my milestones. While I did not have the actual sensors to test with, the online manuals allowed for me to create the framework for the API that would only require some minimal change and testing once the components came in. 

The other major aspect of this project that I worked on was creating the measurement and calibration implementation. While this is still based on the mock-up API for some sensors that had yet to arrive, I was able to implement the majority of the methods functionality, and will be testing this implementation once the physical components can be assembled. As for the calibration, I have been reading the documentation for the sensors and have been creating a calibration system that will attempt to calibrate all the sensors in parallel using a common set of measurement points.

As for the next semester, my main goal is to finish prototyping the device once the sensors and accessories arrive, and begin briefly testing the implementation of all functions that relied on the mock-up. Once I can ensure that this work has been completed, I will be focusing on the I/O implementation and data storage. Once these final major features are complete, I will be completely focusing on extensive testing of both the software and physical design, and working towards a final physical device design.

Overall, I am fairly satisfied with how I have continued to make progress on this project despite supply chain issues. While not an ideal situation, I believe that I have been able to still meet the milestones I initially setup for this project, and will continue to make good progress towards completion. I believe the most time-consuming portion of this project will be the testing of features and building the final design, which could easily grow into larger milestones than initially expected. However, I still believe that the remaining milestones are reasonable and this project will be completed by the expected deadline.

### Final Self Assessment
Overall, I am very satisfied with the work I was able to achieve over the course of this project, despite the many challenges that emerged along the way. One of the largest skills I was able to build upon was perseverance when faced with unknown issues, and learning how to restructure a project so that I was still able to accomplish many of the goals I set out to complete. With the delay of major components needed to build the physical prototype, I decided that it would make more sense to begin working on a simulation that emulated the sensors. This was challenging, since it required thorough reading of the documentation for a product that I did not design, and it had to be done correctly since I didn’t have the means of testing it directly. This taught me the importance of good documentation, as well as the importance of selecting technologies that are well documented when designing a project that uses said technologies.

I believe that this restructuring was successful, as it allowed me to implement and develop most of the software functionality that I originally had included in my milestones. Furthermore, I was able to learn about cross-application interactions, which was not my original expectation. As for other obstacles along the way, building the simulation programs took far longer than I originally expected, which really delayed my original deadlines. The environment in which the programs needed to run in turned out to be very complicated, and I had to learn more about file systems and access permissions on a modern day operating system.

While my project was done as a team of one, I still learned many things about working on projects that extend over a long period of time. One of the key takeaways was the importance  on identifying when a task is complete, and knowing when its time to consider a feature good enough to move on. Many times during this project I was not satisfied with how complete a feature or task was but, as a solo member, I knew that I needed to move on and re-visit it at a later date. This was challenging as I wanted to make everything perfect, but I knew that I had to manage my time effectively to achieve my goals.

One aspect of being a team of one that did not go as well as I wanted was the burnout that can occur when working on the same section of software from start to finish. Many times, I found that I needed to take a break from certain areas of the project so that I could mentally reset and come back to a problem with a fresh view. However, since my project’s milestones were so linear, this was not always possible. In retrospect, I think that I could have structured this project a bit more effectively, allowing for more areas to be worked on in parallel if I needed a break from a particular section.

## Summary of Hours and Justification

### Hours Breakdown Table
<table>
  <tr>
    <th>Milestone</th>
    <th>Fall Term</th>
    <th>Spring Term</th>
    <th>Total</th>
  </tr>
  <tr>
    <td>Milestone 1</td>
    <td>15</td>
    <td>0</td>
    <td>15</td>
  </tr>
  <tr>
    <td>Milestone 2</td>
    <td>50</td>
    <td>0</td>
    <td>50</td>
  </tr>
  <tr>
    <td>Milestone 3</td>
    <td>0</td>
    <td>30</td>
    <td>30</td>
  </tr>
  <tr>
    <td>Milestone 4</td>
    <td>0</td>
    <td>20</td>
    <td>20</td>
  </tr>
  <tr>
    <td>Milestone 5</td>
    <td>0</td>
    <td>10</td>
    <td>10</td>
  </tr>
  <tr>
    <td>Milestone 6</td>
    <td>0</td>
    <td>15</td>
    <td>15</td>
  </tr>
  <tr>
    <td>Other</td>
    <td>15</td>
    <td>15</td>
    <td>30</td>
  </tr>
  <tr>
    <td><strong>Totals</strong></td>
    <td><strong>80</strong></td>
    <td><strong>90</strong></td>
    <td><strong>170</strong></td>
  </tr>
</table>

### Justification of Hours
Since this was an individual project, I chose to summarize the hours in relation to each milestone, or an other category for non-milestone hours. On average,
about 5 hours of work was done each week in accordance with a milestone.

#### Fall Other Hours
Outlined the project repository and began drafted the project description. Wrote my individual capstone assignment and began gathering 
requirements for the project. Finished collecting user stories and created the design diagrams that guided the project design. Overall, these
hours mainly revolved around the assignments for the course.


#### Milestone 1 - Sensor Selection
This milestone involved selecting which microcontroller, sensors, battery, physical connectors, and I/O that I would need to prototype the physical device.
This involved comparing cost, documentation, compatibility with microcontrollers, and other factors for each component. The longest components to decide on
were the HWT905-TTL and LRF60M-10PH sensors, but I ultimately decided the order these after some preliminary reading of their documentation. as they seemed
to be well designed. This milestone also involved looking at some useful code libraries for speeding up development, specifically learning NumPy for vector
mathematics.

#### Milestone 2 - Device Simulation (Sensors)
This was the most time-consuming milestone of the entire project, as it involved not only writing a large amount of code, but because it involved translating
documentation into an accurate code simulation. I first starting by implementing the HWT905-TTL inclinometer and magnetometer, which involved countless hours
of reading the documentation, learning about interprogram communication over a file system, and general debugging. This was by far the largest portion of the
software, and was written entirely in C/C++, which contributed to the large number of hours. Next, I moved onto implementing the LRF60M-10PH laser range finder,
which was much smaller than the HWT905-TTL, but still took a considerable amount of time. Most of the issues with interprogram communication and general struggles
with C/C++ had been resolved after writing the first simulation, however, having to read a new set of documentation and maintaining structure between both
sensors contributed to a milestone that totaled to just about 50 hours of total work, and many sleepless nights.

#### Milestone 3 - Sensor API
This was the second largest milestone of the entire project, but moved considerably faster than Milestone 1. Since I had become quite adept at understanding
the documentation for the sensors, this allowed me to develop the Sensor API fairly quickly in comparison. Furthermore, using Python allowed for some faster
production of code, although I had become quite used to C/C++ by this point. From the size of the code, this was much smaller as I just had to make calls
to the sensor simulations, and correctly modify the input and output files. One of the largest time sinks during this milestone came from debugging the
issues with race conditions and incorrect code, but overall this went fairly fast.

#### Milestone 4 - Measurement & Calibration
This was the third largest milestone of the entire project, but suprisingly only took a few weeks worth of work to get the entire project to begin looking
like a success. Similar to the Sensor API, this mostly involved just writing API calls to the sensor programs. However, the largest time sink for this
particular milestone was calculating the cardinal heading of the device. This turned out to be a fairly involved process, and led to many hours of learning
about magnetism and various mathematical equations for projecting the magnetic field onto the acceleration field to extract the heading vector. This took longer
than expected, but I was still able to complete this particular milestone within a resonable amount of time.

#### Milestone 5 - Device Simulation (I/O)
This was the smallest milestone of the entire project, but also contributed to the polish of the finish product. This mainly involved creating an intuitive
user interface, as well as adding some additional logging to the sensor simulations so that user could see what was happening in real-time. This milestone
also enabled to ability to begin testing most of the functionality of the project, which I have included in the 10 hours for this milestone. Overall, while
this milestone seems small, it contributed a huge amount towards the results of the project.

#### Milestone 6 - Data Storage
This final milestone involved just taking the raw output of the device, and allowing the user to save it to a .txt file on an SD card. The majority of the
time accounted for in this milestone involved learning about file manipulation and appending, since I did not want the device to slow down when writing to
the SD card as the data points grew. Therefore, this involved a large amount trying new solutions, and scrapping old inefficient ones as I continued improving
this process.

#### Spring Other Hours
Most of these other hours for the spring involve completing the various capstone assignments, as well as re-designing and improving the navigation
of the code repository. The largest single item that contributed towards these hours was the Expo poster, as well as preparing for the Expo itself. Since
I am fairly inexperienced at poster design, roughly 6 hours were spent just creating and refining the final poster design.

## Summary of Expenses

<table>
  <tr>
    <th>Item(s)</th>
    <th>Allocated Funds</th>
  </tr>
  <tr>
    <td>Sensors</td>
    <td>$250</td>
  </tr
  <tr>
    <td>Microcontroller</td>
    <td>$100</td>
  </tr>
  <tr>
    <td>Additional/Accessories</td>
    <td>$150</td>
  </tr>
  <tr>
    <td><b>Total</b></td>
    <td><b>$500</b></td>
  </tr>
</table>

 ## Appendix
 * [LRF60M-10PH Sensor Documentation](https://github.com/DarkNomads/DistoY/blob/7e34fea71461653f07cd023b3e609e29f35a7c9d/misc/LRF100M10PH-datasheet.pdf)
 * [HWT905-TTL Sensor Documentation](https://github.com/DarkNomads/DistoY/blob/7e34fea71461653f07cd023b3e609e29f35a7c9d/misc/WIT%20Standard%20Communication%20Protocol.pdf)
