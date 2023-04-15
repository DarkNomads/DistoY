# Summary of Hours

## Hours Breakdown Table
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
    <td><strong>170</strong><</td>
  </tr>
</table>

## Justification of Hours
Since this was an individual project, I chose to summarize the hours in relation to each milestone, or an other category for non-milestone hours. On average,
about 5 hours of work was done each week in accordance with a milestone.

### Fall Other Hours
Outlined the project repository and began drafted the project description. Wrote my individual capstone assignment and began gathering 
requirements for the project. Finished collecting user stories and created the design diagrams that guided the project design. Overall, these
hours mainly revolved around the assignments for the course.


### Milestone 1 - Sensor Selection
This milestone involved selecting which microcontroller, sensors, battery, physical connectors, and I/O that I would need to prototype the physical device.
This involved comparing cost, documentation, compatibility with microcontrollers, and other factors for each component. The longest components to decide on
were the HWT905-TTL and LRF60M-10PH sensors, but I ultimately decided the order these after some preliminary reading of their documentation. as they seemed
to be well designed. This milestone also involved looking at some useful code libraries for speeding up development, specifically learning NumPy for vector
mathematics.

### Milestone 2 - Device Simulation (Sensors)
This was the most time-consuming milestone of the entire project, as it involved not only writing a large amount of code, but because it involved translating
documentation into an accurate code simulation. I first starting by implementing the HWT905-TTL inclinometer and magnetometer, which involved countless hours
of reading the documentation, learning about interprogram communication over a file system, and general debugging. This was by far the largest portion of the
software, and was written entirely in C/C++, which contributed to the large number of hours. Next, I moved onto implementing the LRF60M-10PH laser range finder,
which was much smaller than the HWT905-TTL, but still took a considerable amount of time. Most of the issues with interprogram communication and general struggles
with C/C++ had been resolved after writing the first simulation, however, having to read a new set of documentation and maintaining structure between both
sensors contributed to a milestone that totaled to just about 50 hours of total work, and many sleepless nights.

### Milestone 3 - Sensor API
This was the second largest milestone of the entire project, but moved considerably faster than Milestone 1. Since I had become quite adept at understanding
the documentation for the sensors, this allowed me to develop the Sensor API fairly quickly in comparison. Furthermore, using Python allowed for some faster
production of code, although I had become quite used to C/C++ by this point. From the size of the code, this was much smaller as I just had to make calls
to the sensor simulations, and correctly modify the input and output files. One of the largest time sinks during this milestone came from debugging the
issues with race conditions and incorrect code, but overall this went fairly fast.

### Milestone 4 - Measurement & Calibration
This was the third largest milestone of the entire project, but suprisingly only took a few weeks worth of work to get the entire project to begin looking
like a success. Similar to the Sensor API, this mostly involved just writing API calls to the sensor programs. However, the largest time sink for this
particular milestone was calculating the cardinal heading of the device. This turned out to be a fairly involved process, and led to many hours of learning
about magnetism and various mathematical equations for projecting the magnetic field onto the acceleration field to extract the heading vector. This took longer
than expected, but I was still able to complete this particular milestone within a resonable amount of time.

### Milestone 5 - Device Simulation (I/O)
This was the smallest milestone of the entire project, but also contributed to the polish of the finish product. This mainly involved creating an intuitive
user interface, as well as adding some additional logging to the sensor simulations so that user could see what was happening in real-time. This milestone
also enabled to ability to begin testing most of the functionality of the project, which I have included in the 10 hours for this milestone. Overall, while
this milestone seems small, it contributed a huge amount towards the results of the project.

### Milestone 6 - Data Storage
This final milestone involved just taking the raw output of the device, and allowing the user to save it to a .txt file on an SD card. The majority of the
time accounted for in this milestone involved learning about file manipulation and appending, since I did not want the device to slow down when writing to
the SD card as the data points grew. Therefore, this involved a large amount trying new solutions, and scrapping old inefficient ones as I continued improving
this process.

### Spring Other Hours
Most of these other hours for the spring involve completing the various capstone assignments, as well as re-designing and improving the navigation
of the code repository. The largest single item that contributed towards these hours was the Expo poster, as well as preparing for the Expo itself. Since
I am fairly inexperienced at poster design, roughly 6 hours were spent just creating and refining the final poster design.

