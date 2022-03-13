"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {

	window.setInterval(function() {sendDrumCommand('stream')}, 1000);

	socket.on('commandVideo', function(result) {
		$('#monitor-stream');
	});
	
});

function sendPrimeCommand(message) {
	socket.emit('video', message);
};