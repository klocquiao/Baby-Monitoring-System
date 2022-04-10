"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {
	window.setInterval(function() {sendMonitorCommand('checkForMotion')}, 1000);
	window.setInterval(function() {sendMonitorCommand('checkForRecording')}, 3000);

	//Test1
	$('#functionRecord').click(function(){
		sendMonitorCommand("record");
	});
	//Test2
	$('#functionLullaby1').click(function(){
		sendMonitorCommand("lullaby1");
	});
	//Test3
	$('#functionLullaby2').click(function(){
		sendMonitorCommand("lullaby2");
	});
	//Test4
	$('#functionMDFrame').click(function(){
		sendMonitorCommand("mdframe");
	});

	// Get the modal
	var modal = document.getElementById("myModal");
	// Get the button that opens the modal
	var btn = document.getElementById("modal1");
	// Get the <span> element that closes the modal
	var span = document.getElementsByClassName("close")[0];
	// When the user clicks on the button, open the modal
	btn.onclick = function() {
		modal.style.display = "block";
	}
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

<<<<<<< Updated upstream
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

=======
	//Test5
	$('#modal1').click(function(){
		sendMonitorCommand("modal1");
	});
	
	
>>>>>>> Stashed changes
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