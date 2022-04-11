"use strict";
// Client-side interactions with the browser.

var isMotionNotified = false;

function closeModal() {
  const modal = document.getElementById("myModal");
  modal.style.display = "none";
  $('#modal-content').text("");
}

var lastHeard = 0

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {
	window.setInterval(function() {sendMonitorCommand('checkForMotion')}, 1000);
	window.setInterval(function() {sendMonitorCommand('checkForRecording')}, 3000);
  	window.setInterval(function() {sendMonitorCommand('checkForAudio')}, 1000);

	// Get the <span> element that closes the modal
	var span = document.getElementsByClassName("close")[0];
	// When the user clicks on <span> (x), close the modal
	span.onclick = closeModal;
	// When the user clicks anywhere outside of the modal, close it
	window.onclick = closeModal;

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

	socket.on('commandRecord', function(result) {
		preventRecording();
	});

	socket.on('commandUpdateFrame', function(result) {
    isMotionNotified = false;
	});	

	socket.on('commandUpdateMotion', function(result) {
		// Display modal
    if (result == "motion" && !isMotionNotified) {
      isMotionNotified = true;
      const modal = document.getElementById("myModal");
      modal.style.display = "block";
      $('#modal-content').text("Motion Detected...");
    }
	});

	socket.on('commandUpdateRecording', function(result) {
		if (result == "noRecord") {
			allowRecording();
		}
		else {
			preventRecording();
		}
	});

  socket.on('commandAudioDetected', (result) => {
    if (result === "audioDetected") {
		lastHeard = 0;
      $('#audio-detection').text("I hear sound...");
    } else {
		lastHeard++;
		let formattedTime = format(lastHeard)
      $('#audio-detection').text(`Audio last detected ${formattedTime} ago`);
    }
  })
});

//https://stackoverflow.com/questions/28705009/how-do-i-get-the-server-uptime-in-node-js
function format(seconds) {
    function pad(s){
        return (s < 10 ? '0' : '') + s;
      }
      var hours = Math.floor(seconds / (6060));
      var minutes = Math.floor(seconds % (6060) / 60);
      var seconds = Math.floor(seconds % 60);

      return pad(hours) + ':' + pad(minutes) + ':' + pad(seconds);
}

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