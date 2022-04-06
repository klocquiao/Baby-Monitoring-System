"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	$('#functionTest').click(function(){
		sendMonitorCommand("test");
	});

	$('#functionRecord').click(function(){
		sendMonitorCommand("record");
	});	
	
	$('#functionUpdateFrame').click(function(){
		sendMonitorCommand("updateFrame");
	});

	socket.on('commandTest', function(result) {
		$('#status-text').text(result);
	});

	socket.on('commandRecord', function(result) {
		$("#functionRecord").prop("value", "Recording...");
		$("#functionRecord").prop('disabled', true);

		setTimeout(function() {
            $("#functionRecord").prop('disabled', false);
		}, 20000);
	});


	socket.on('commandUpdateFrame', function(result) {
		// Reset the initial frame;
	});
});

function sendMonitorCommand(message) {
	socket.emit('monitor', message);
};