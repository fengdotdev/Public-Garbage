const pulseDisplay =  document.getElementById("pulseDisplay");

pulseDisplay.innerText = 0;

var rate = 0;

document.getElementById('connect')
	.addEventListener('click', () => {
		BluetoothPulseMonitor.connect()
			.then(() => {
				BluetoothPulseMonitor.addEventListener('change', (value) => {
					console.log(value);
					rate = value ? (Math.round((60 / value) * 10) / 10) : 0;
					pulseDisplay.innerText = value ? value : '';

				});
			});
	});
