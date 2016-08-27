'use strict';
let five = require("johnny-five");
let board = new five.Board();

board.on("ready", function() {
    // Create an Led on pin 13
    blinkLed();
});


const blinkLed = () => {
    let led = new five.Led(13);
    led.blink(500);
    setTimeout(() => {
        led.stop().off();
    }, 5000)
}
