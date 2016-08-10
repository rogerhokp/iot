'use strict';
let five = require("johnny-five");
let board = new five.Board();
const sensorPin = 3;
const ledPin = 11;

board.on("ready", function() {
    //Vibration Sensor :so9sad
    this.samplingInterval(5);

    //LED pwm
    this.pinMode(ledPin, five.Pin.PWM);
    const led = new five.Led(ledPin);

    //
    var sensor = new five.Sensor.Digital({
        pin: sensorPin,
        freq: 1
    });

    // let sensor = new five.Sensor({
    //     pin: 'A0',
    //     freq: 1
    // })



    sensor.on("change", function(value) {
        // console.log(value);
        if (value == 0) {
            console.log('fuck');
            led.pulse(120);
            sensor.disable();
            setTimeout(() => {
                led.stop().off();
                sensor.enable();
            }, 500);
        }

    });

});
