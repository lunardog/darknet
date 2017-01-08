import darknet

darknet.parse_network_cfg("cfg/yolo.cfg")
darknet.load_weights("data/yolo.weights")
