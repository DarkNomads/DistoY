# Final Report

## Project Abstract
DistoY is a cave surveying device aimed at providing cavers with a larger variety of functionality for surveying at a much lower cost\
than current products on the market. The DistoY will allow for taking distance measurements that can also record angles, track cardinal\
direction, and store data for later use. Furthermore, it will also be built to survive in the harsh conditions of caves, such as being\
dropped from heights, exposed to lots of dust, cold temperatures, and wetness or submersion in water. 

## Project Description

## User Stories
1. As a caver, I want to measure distance between two different points.
2. As a caver, I want to determine the angle of a distance measurement.
3. As a caver, I want to know what cardinal direction I am generating a measurement towards.
4. As a caver, I want to ensure that all measurements are accurate and within tolerable error margins.
5. As a caver, I want to store measurements for future use.

## Design Digrams
![image](https://user-images.githubusercontent.com/33441174/229302583-3a7dd901-de8a-4fce-8919-3f58f88e40f4.png)

### D0 - High-Level Overview
![image](https://user-images.githubusercontent.com/33441174/229302589-dbbc181b-107b-4a06-9348-de0b8d05200b.png)

### D1 - Sub-Component Expansion
![image](https://user-images.githubusercontent.com/33441174/229302601-523e7c4e-a8b3-4487-98e5-0dabaf5c84f7.png)

### D2 - Addtional Functionality Detail
![image](https://user-images.githubusercontent.com/33441174/229302607-77dff304-d942-4643-908f-6843d0f43a18.png)

## Milestones & Timeline

### Milestones

#### 1. Sensor/Accessory Selection
<ul>
  <b>Description</b>: Select the microcontroller, sensors, battery, physical connectors, I/O, etc. needed for the device.
  <br/>
  <b>Deliverable(s)</b>: Order list all of the physical components.
</ul>

#### 2. Physical Device Prototyping
<ul>
  <b>Description</b>: Assemble the sensors and other components for the device into a workable prototype.
  <br/>
  <b>Deliverable(s)</b>: All sensors and major components connected via a breadboard.
</ul>

#### 3. Sensor API Implementation
<ul>
  <b>Description</b>: Design the API to control sending commands to each sensor, as well as retrieving the values from each sensor.
  <br/>
  <b>Deliverable(s)</b>: A functional API that can interact with the device's sensors.
</ul>

#### 4. Measurement/Calibration Implementation
<ul>
  <b>Description</b>: Design the data processor component of the software, and implement the functionality for taking a measurement and calibrating the appropriate sensors.
  <br/>
  <b>Deliverable(s)</b>: A functional piece of software that interfaces with the Sensor API to perform measuring and calibration.
</ul>

#### 5. I/O Implementation
<ul>
  <b>Description</b>: Design the physical I/O for the device, as well as the software needed to translate this into software commands.
  <br/>
  <b>Deliverable(s)</b>: A device with working I/O.
</ul>

#### 6. Storage and Metadata Implementation
<ul>
  <b>Description</b>: Implement storage capability for the device, as well as adding additional metadata to the measurements.
  <br/>
  <b>Deliverable(s)</b>: Device memory can store and retrieve formatted data through the software.
</ul>

#### 7. Functionality Testing
<ul>
  <b>Description</b>: Test the accuracy and functionality of the software/sensors, and refine design until it is within correct tolerances.
  <br/>
  <b>Deliverable(s)</b>: A device with completed software.
</ul>

#### 8. Environmental Testing
<ul>
  <b>Description</b>: Test the prototype in various cave or cave-like conditions, and determine necessary changes for the final design.
  <br/>
  <b>Deliverable(s)</b>: A list of tests performed and improvements for the physical design of the device.
</ul>

#### 9. Final Physical Device Design
<ul>
  <b>Description</b>: Using data collected from the environmental testing milestone, design and build the device according to final specifications.
  <br/>
  <b>Deliverable(s)</b>: A finished product that can be used in cave-surveying scenarios. 
</ul>

### Timeline
<table>
  <tr>
    <th>Milestone</th>
    <th>Planned Start Date</th>
    <th>Planned Completion Date</th>
  </tr>
  <tr>
    <td>1. Sensor/Accessory Selection</td>
    <td>2022/10/03</td>
    <td>2022/10/10</td>
  </tr>
  <tr>
    <td>2. Physical Device Prototyping</td>
    <td>2022/10/10</td>
    <td>2022/10/24</td>
  </tr>
  <tr>
    <td>3. Sensor API Implementation</td>
    <td>2022/10/24</td>
    <td>2022/11/14</td>
  </tr>
  <tr>
    <td>4. Measurement/Calibration Implementation</td>
    <td>2022/11/14</td>
    <td>2022/11/28</td>
  </tr>
  <tr>
    <td>5. I/O Implementation</td>
    <td>2022/11/28</td>
    <td>2022/12/09</td>
  </tr>
  <tr>
    <td>6. Storage and Metadata Implementation</td>
    <td>2023/01/16</td>
    <td>2023/01/30</td>
  </tr>
  <tr>
    <td>7. Functionality Testing</td>
    <td>2023/01/30</td>
    <td>2023/02/20</td>
  </tr>
  <tr>
    <td>8. Environmental Testing</td>
    <td>2023/02/20</td>
    <td>2023/03/06</td>
  </tr>
  <tr>
    <td>9. Final Physical Device Design</td>
    <td>2023/03/06</td>
    <td>2023/03/21</td>
  </tr>
</table>

## Project Slideshow Presentation
* [Link Text]()

## Self Assessment Essay

## Professional Biography

My name is Isaac Kirsch, and I am a fifth-year computer science student at the University of Cincinnati.

### Contact Information
I can be contacted through my University of Cincinnati email address: kirschic@mail.uc.edu

### Co-op Work Experience
#### Software Engineer - Idaho National Laboratory ( 2020.05.01 - present )
I have been co-oping with the INL since my first co-op rotation (Summer 2020) and have completed all four of my 
co-op rotations with them. I work primarily in the Software Engineering Team at the Materials and Fuels Complex,
which handles the development and maintenance of applications used to study and track nuclear material.
Specifically, I have:

* Designed software that allows for modern interfacing with legacy technologies.
* Developed modern web applications that allow for backwards compatibility with older computer systems.
* Maintained databases and systems that work with critical data.
* Implemented automated testing and deployment for large-scale software projects.
* Communicated with stakeholders to determine application requirements and restrictions.
* Collaborated with various team members on a daily basis across multiple projects.

### Technical Skills
* **Programming** - Ruby (w/Rails), C, C++, Assembly (x86), FORTRAN, Python
* **Web Development** - Typescript, HTML, SCSS
* **Database Programming** - SQL, Redis (w/Sidekiq)

### Project Sought
* The project I will be completing during my capstone involves creating a hand-held, paperless cave surveying device.
* The purpose of this capstone is to create an open-source, simple, and affordable option for surveying to cavers across the world. 
* In more specific detail, I will be creating both a software API in order to read/write data from the sensors, and designing the
hardware to withstand the harsh conditions of caving, such as being: sturdy, water/dust-resistant, and power efficient.

## Budget

<table>
  <tr>
    <th>Item(s)</th>
    <th>Allocated Funds</th>
  </tr>
  <tr>
    <td>Sensors</td>
    <td>$250</td>
  </tr>
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
* [Constraints Essay](https://github.com/DarkNomads/DistoY/blob/d609189bcb37159efa3de04caf9547e749fab952/Constraint%20Essay.md)

