"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {
	var recordTimer;
	window.setInterval(function() {sendMonitorCommand('checkForMotion')}, 1000);

	$('#functionTest').click(function(){
		sendMonitorCommand("test");
	});

	$('#functionRecord').click(function(){
		if ($('#functionRecord').attr("value") == "Record") {
			sendMonitorCommand("record");
		}
		else {
			sendMonitorCommand("stopRecord");
		}
	});	
	
	$('#functionUpdateFrame').click(function(){
		sendMonitorCommand("updateFrame");
	});

	socket.on('commandTest', function(result) {
		$('#status-text').text(result);
	});

	socket.on('commandRecord', function(result) {
		$("#functionRecord").prop("value", "Recording...");

		recordTimer = setTimeout(function() {
			$("#functionRecord").prop("value", "Record");
		}, 60000);
	});

	socket.on('commandStopRecord', function(result) {
		$("#functionRecord").prop("value", "Record");
		clearTimeout(recordTimer);

		setTimeout(function() {
			$("#functionRecord").prop("value", "Record");
		}, 30000);
	});


	socket.on('commandUpdateFrame', function(result) {
		// Reset the initial frame;
	});	

	socket.on('commandUpdateMotion', function(result) {
		$('#status-text').text(result);
	});
});

function sendMonitorCommand(message) {
	socket.emit('monitor', message);
};

function stopRecording() {
	$("#functionRecord").prop("value", "Record");
	clearTimeout(recordTimer);

	$("#functionRecord").prop('disabled', true);
	setTimeout(function() {
		$("#functionRecord").prop('disabled', false);
	}, 5000);
}