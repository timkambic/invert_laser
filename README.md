#invert_laser
Node that inverts laser. Used when LIDAR is mounted top down.

### Subscribed topics
* `/inv_scan(sensor_msgs/LaserScan)` Laser scan to be inverted

### Published topics
* `/scan (sensor_msgs/LaserScan)` Inverted laser scan