# Test Results
## Sensor API (SA) Tests
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

## Data Processor (DP) Tests
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

## I/O Controller (IO) Tests
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

## Physical Device (PD) Tests
* These tests were deprecated, as the physical device was not finished.
