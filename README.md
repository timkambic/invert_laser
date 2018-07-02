# invert_laser #
ROS node that inverts laser. Used when LIDAR is mounted upside down.

### Subscribed topics
* `/scan(sensor_msgs/LaserScan)` Laser scan to be inverted

### Published topics
* `/scan_inv (sensor_msgs/LaserScan)` Inverted laser scan

### Parameters
* `out_frame (string default:"")` output TF frame of message. If left empty it will be same as input frame.

### Usage
See `invert_laser/launch/invert.launch` for example.