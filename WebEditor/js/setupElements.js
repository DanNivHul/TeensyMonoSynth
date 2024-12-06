// Set option values for the CC and Channel dropdown lists

var numElements = 10;

var channelOptions = "";
for(var i = 1 ; i < 17; i++) {
    channelOptions += "<option>"+ i +"</option>";
}

var ccOptions = "";
for(var i = 0 ; i < 128; i++) {
    ccOptions += "<option>"+ i +"</option>";
} 

for(var i = 0; i < numElements; i++) {
    var idValue = "pot" + i + "Value";
    var idCC = "pot" + i + "CC";
    var idChannel = "pot" + i + "Channel";

    document.getElementById(idCC).innerHTML = ccOptions;
    document.getElementById(idChannel).innerHTML = channelOptions;	
}