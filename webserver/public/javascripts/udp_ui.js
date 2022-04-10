"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {
	window.setInterval(function() {sendMonitorCommand('checkForMotion')}, 1000);
	window.setInterval(function() {sendMonitorCommand('checkForRecording')}, 3000);

	// Get the <span> element that closes the modal
	var span = document.getElementsByClassName("close")[0];
	// When the user clicks on <span> (x), close the modal
	span.onclick = function() {
		modal.style.display = "none";
	}
	// When the user clicks anywhere outside of the modal, close it
	window.onclick = function(event) {
		if (event.target == modal) {
			modal.style.display = "none";
		}
	} 

	$('#functionRecord').click(function(){
		sendMonitorCommand("record");
	});	
	
	$('#functionUpdateFrame').click(function(){
		sendMonitorCommand("updateFrame");
	});

  $('#functionStartPlayback1').click(function(){
		sendMonitorCommand("startPlayback1");
	});	

  $('#functionStartPlayback2').click(function(){
		sendMonitorCommand("startPlayback2");
	});	

  $('#functionStopPlayback').click(function(){
		sendMonitorCommand("stopPlayback");
	});

	$('#modal1').click(function(){
		sendMonitorCommand("checkForMotion");
	});
	
	socket.on('commandTest', function(result) {
		$('#status-text').text(result);

	});

	socket.on('commandRecord', function(result) {
		preventRecording();
	});

	socket.on('commandUpdateFrame', function(result) {
	});	

	socket.on('commandUpdateMotion', function(result) {
    $('#status-text').text(result);

		// Display modal
    var modal = document.getElementById("myModal");
    modal.style.display = "block";
    $('#modal-content').text(result);
	});

	socket.on('commandUpdateRecording', function(result) {
		if (result == "noRecord") {
			allowRecording();
		}
		else {
			preventRecording();
		}
	});
});

function sendMonitorCommand(message) {
	socket.emit('monitor', message);
};

function allowRecording() {
	$("#functionRecord").prop("value", "Record");
	$("#functionRecord").prop('disabled', false);
}

function preventRecording() {
	$("#functionRecord").prop("value", "Recording...");
	$("#functionRecord").prop('disabled', true);
}