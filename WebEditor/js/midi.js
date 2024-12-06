// Global Variables
var midi;
var deviceOutputID;
var outputConnectedPrev = false;

// Global Constants
var manufacturerID1 = 0x09;
var manufacturerID2 = 0x03;
var manufacturerID3 = 0x03;
var infoCommand = 0x1f;
var editCommand = 0x0e;



if (navigator.requestMIDIAccess) {
    navigator.requestMIDIAccess({
    sysex: true
    }).then(onMIDISuccess, onMIDIFailure);
} else {
    alert("No MIDI support in your browser.");
}



function onMIDISuccess(midiAccess) {
    setMIDI(midiAccess);

    // Callback for when controllers are connected / disconnected
    midiAccess.onstatechange = function(e) {
        console.log("State changed");
        console.log(e.port.name, e.port.manufacturer, e.port.state);
        setMIDI(midiAccess);
    };

}



function setMIDI(midiAccess) {
    midi = midiAccess;

    // Input
    for(var input of midiAccess.inputs.values()) {
        console.log("Input connected to: " + input.name);
        input.onmidimessage = onMIDIMessage;
    }

    // Output
    var outputConnected = false;

    for(var output of midiAccess.outputs.values()) {
        console.log("Output connected to: " + output.name);
        deviceOutputID = output.id;
        outputConnected = true;
    }

    if(outputConnected && !outputConnectedPrev) {
        //requestConfig();
    }
    outputConnectedPrev = outputConnected;


    // Connection status
    if(outputConnected) {
        document.getElementById("connectionStatus").innerHTML = "Connected: " + output.name;
    } else {
        document.getElementById("connectionStatus").innerHTML = "No Device Connected";
    }

}



function searchMIDI() {
    if (navigator.requestMIDIAccess) {
        navigator.requestMIDIAccess({
            sysex: true
        }).then(onMIDISuccess, onMIDIFailure);
    } else {
        alert("No MIDI support in your browser.");
    }
}



function onMIDIFailure(error) {
    console.log(error);
}



function onMIDIMessage(message) {
    console.log(message);
    var command = message.data[0];

    if(command == 0xf0) {
        console.log("Received SysEx Message!");
        ReadSysEx(message.data);
    } else if(command >> 4 == 0x0b) {
        console.log("Received CC Message!");
        handleCC(message.data);
    }
}



//==============================================================================================================
//  CC
//==============================================================================================================

function handleCC(ccData) {
    // Check data is valid length
    if(ccData.length != 3)
    {
        console.log("Invalid CC message");
        return;
    }

    // Extract CC and value from data
    var controllerChannel = ccData[0] - 175;
    var controllerCC = ccData[1];
    var controllerValue = ccData[2];

    // Compare CC and channel from controller to CCs and channels on webpage
    // If there is a match, update the corresponding value field on webpage with the new controller value
    // And rotate the knob to the corresponding angle
    for(var i=0; i<10; i++)
    {
        var idCC = "pot" + i + "CC";
        var idChannel = "pot" + i + "Channel";

        var elementCC = document.getElementById(idCC).value;
        var elementChannel = document.getElementById(idChannel).value;

        if(controllerCC == elementCC && controllerChannel == elementChannel)
        {
            var idValue = "pot" + i + "Value";
            document.getElementById(idValue).innerHTML = controllerValue;

            var idKnob = "pot" + i;
            var knob = document.getElementById(idKnob);
            var angle = 270 / 127 * controllerValue - 135;
            knob.style.transform = "rotate(" + angle + "deg)";
        }

    }

}



//==============================================================================================================
//  Sysex
//==============================================================================================================

function ReadSysEx(sysExData) 
{
    //console.log(sysExData);
    
    if(sysExData.length <= 5)	// [SysExStart, Manufacturer, Manufacturer, Manufacturer, SysExEnd]	
    {
        console.log("Empty SysEx");
        return;
    }

    if(!(sysExData[1] == 0x09 && sysExData[2] == 0x03 && sysExData[3] == 0x03))
    {
        console.log("This SysEx is not meant for us");
        return;
    }

    var command = sysExData[4];
    switch (command) 
    {
        case 0x0f:	
            // c0nFig - current controller configuration
            console.log("Received controller configuration!");
            if(sysExData.length != 30)
            {
                console.log("Controller configuration is the wrong length");
                return;
            }
            displayConfig(sysExData);
            break;

        default:
            console.log("Received unknown SysEx command");
            break;
    }
    
}



function displayConfig(sysExData) 
{    
    for(var i=0; i<10; i++)
    {
        var idChannel = "pot" + i + "Channel";
        var pointerChannel = i + 9;
        document.getElementById(idChannel).selectedIndex = sysExData[pointerChannel] - 1;

        var idCC = "pot" + i + "CC";
        var pointerCC = i + 19;
        document.getElementById(idCC).selectedIndex = sysExData[pointerCC];
    }
    
    console.log("Successfully retrieved controller configuration!");
    //alert("Successfully retrieved controller configuration.");
}



function requestConfig() 
{
    console.log("Sending SysEx");
    var sysExMessage = [0xf0, manufacturerID1, manufacturerID2, manufacturerID3, infoCommand, 0xf7];
    var output = midi.outputs.get(deviceOutputID);
    output.send(sysExMessage);
}



function uploadConfig() 
{
    var sysExMessage = [];
    sysExMessage[0] = 0xf0; // SysEx Start
    sysExMessage[1] = manufacturerID1;
    sysExMessage[2] = manufacturerID2;
    sysExMessage[3] = manufacturerID3;
    sysExMessage[4] = editCommand;
    sysExMessage[25] = 0xf7; // SysEx Finish

    for(var i=0; i<10; i++)
    {
        var idChannel = "pot" + i + "Channel";
        var channel = document.getElementById(idChannel).value;
        sysExMessage[5 + i] = channel;

        var idCC = "pot" + i + "CC";
        var CC = document.getElementById(idCC).value;
        sysExMessage[15 + i] = CC;
    }

    console.log("Sending SysEx");
    var output = midi.outputs.get(deviceOutputID);
    output.send(sysExMessage);
}

function sendControlChange(controlNumber, value) {
    const msg = [0xB0, controlNumber, value];   //[control change on channel 0, controlNumber, value]
    console.log("Sending channel 1, cc: " + controlNumber + ", value: " + value);
    var output = midi.outputs.get(deviceOutputID);
    output.send(msg);
}