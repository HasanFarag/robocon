# Project Requirements


## Project Brief 2017

### Dead Line
The rover shall be completed by 1st week in May.

### Functional Requirements

A remote controlled robotic vehicle is to be designed to take part in a
competition called Robocon. The robotic vehicle must be no larger
than 0.3m x 0.3m. Some clearance will be required so the vehicles dimensions
should be smaller than this. There is no height restriction for the vehicle.

The vehicle shall be capable of autonomously navigating it's way through
a maze. The maze shall be of a substantially different design each time a
competition is or rehearsal is held to prevent any vehicle learning a route
prior to competition.

After completing the maze the vehicle should be remotely controlled and driven
towards a target. The vehicle must be capable of firing ping pong balls at the
target.

### EE1 - Electrical/Electronic Specifications

#### EE1.0 -Power supplies
The maximum voltage of any power supply shall be 12V. Power supplies on board
the vehicle must be DC. Up to two separate power supplies are permitted.

#### EE1.1 - Circuit Protection and Safe Isolation
Suitable fuse protection must be incorporated to minimize the risk of damage to
electrical and electronic circuits.

A safe means of isolating all electrical equipment from the power supply shall
be provided. In addition a means of isolating the supply in an emergency
shall be easily accessible and allow safe stopping of a moving vehicle.

Electrical isolation shall also activate pneumatic air supply shut off valves
and safety release valves to ensure air is fully evacuated from pneumatic systems   

#### EE1.2 Motors
Motor circuits shall be electrically separate from all other systems.
The maximum full load current of any motor shall be no more than 2A.

#### EE1.3 Electronic Monitoring and Control System   
The control system may utilise any type of controller, sensors and actuators
necessary to fulfil the functional requirements of the rover. Any form of
wireless communication may be used provided the radio frequencies and channels
meet [Ofcom interface requirements IR2030](https://www.ofcom.org.uk/__data/assets/pdf_file/0028/84970/ir-2030-july-2017.pdf)

Safety critical systems including mechanical and pneumatic system shall be
monitored and a means of mechanical, electrical/electronic control provided to
activate safety systems.

Safety systems may include pneumatic release valves. Electrically actuated
pressure release valves shall be designed to safely evacuate air from the
pneumatic in the event of electrical power failure or emergency isolation.       

#### EE1.4 Visual Indicators
Each rover shall have a minimum of three indicator lamps for the purposes of
indicating the following functions:

* Power
* Live communication link/Radio control active
* Automated Control active

Other indicators or displays may be included for visual effects.

## Mechanical Specifications

### ME1.0 Maximum dimensions
The robotic vehicle must be no larger than 0.3m x 0.3m. Some clearance will be
required so the vehicles dimensions should be smaller than this.
There is no height restriction for the vehicle.
The full system should be no more than 10kg for safe handling.

### ME1.1 Pneumatics
The maximum pneumatic supply pressure shall be limited to 1Mpa (10Bar).
This pressure shall be monitored locally and electronically. Safety release
valves shall be fitted to ensure the pressure cannot exceed the specified
maximum. Pneumatically and Electrically actuated valves may be used. Where
electrically actuated release valves are used they shall be designed to open
on loss of electrical supply.

Electrically actuated shut off valves shall be provided such that on loss of
the electrical supply shall also shut off pneumatic air supply.

### ME1.2 Table-tennis Ball Firing System
A system for firing table-tennis balls at a target shell be provided.
The ball shall have a diameter of 40mm and a maximum weight of 2.7g.
Table-tennis balls used during the competition shall be supplied by officials.

The firing system may be mechanically, electrically or pneumatically powered.
Control of the firing system may be purely mechanical, electrical or pneumatic.
Electromechanical and Electro-pneumatic control is also permitted.

Whichever control mechanism is used there shall be safety mechanisms to prevent
accidental discharge of a table-tennis ball.

Where electrical, electromechanical or electro-pneumatic control are used they
**must fail safe** in the event of electrical power loss, normal and emergency
electrical isolation.

The system shall have a maximum payload of 5 table-tennis balls.
Loading of table-tennis balls into the firing system may be via manual,
mechanical, electrical or pneumatic means. Whichever system is used it should
be designed to ensure only one table-tennis ball can be loaded into the firing
mechanism. Burst or rapid firing of table-tennis balls is **not** permitted.

## Fabrication and Manufacture
Each teams must produce at least one PCB and use at least two different
manufacturing processes.

All fabrication and manufacturing processes must be risk assessed and safe
working practices carried out at all times.

## Competition Events

### Event 1 - The Maze
Each team will be called in turn to present their rover to the start point of
the maze. Teams may drive their robot into the arena and up to the maze starting
point using remote control. Alternatively they can manually push their rover to
the start position. Only one team member shall be permitted to enter the floor
area and manually position their rover at the maze start line.

Each team shall be required hand control over to competition officials to engage
the rovers automated maze solving mode either remotely or manually by means of
a switch or button on the rover.

No team member may enter the designated unattended operation zone or the
wireless remote control zone during this event.

The rover must successfully negotiate the course maze with no assistance
manually or remotely.

### Event 2 - Scoring  
Each maze will have a target mounted on the far-side of the maze. The position
of this target is not known beforehand.

One team member shall be permitted to enter the wireless control zone.
Competition officials will hand control back over to the team member (operator)
who will remotely drive their rover to the target scoring area. The scoring area
will have a score line on the floor which the rover must not cross.

Once the rover is at or near the score line the operator will aim and fire a
table-tennis ball at the target. Points will be scored depending on the accuracy
of the shot. If there are no direct hits within given number of balls this will
affect the points awarded for accuracy.
