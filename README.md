# MQB steering wheel CAN controller

Arduino firmware for a microcontroller with a FlexCAN interface. It sits on the chassis CAN bus (500 kbit/s) of a VW MQB-platform car. It reads steering wheel button and paddle inputs, and broadcasts button and paddle-shift frames so that a retrofitted steering wheel works with the car.

Written in 2025. CAN IDs and payloads are specific to the target car. Use at your own risk on a vehicle bus.
