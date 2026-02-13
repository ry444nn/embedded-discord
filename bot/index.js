const { Client, GatewayIntentBits } = require('discord.js');
const { token } = require('./config.json');
const axios = require('axios');

// Create a new client instance
const client = new Client({ intents: [GatewayIntentBits.Guilds] });

// When the client is ready, run this code (only once)
client.once('ready', () => {
	console.log('Ready!');
});

client.on('interactionCreate', async interaction => {
	if (!interaction.isChatInputCommand()) return;

	const { commandName } = interaction;

	if (commandName === 'ping') {
		await interaction.reply('Pong!');
	} else if (commandName == 'lighton') {
        axios
        .post('http://192.168.0.219/relay?relay2=on', {})
        .then(res => {
            interaction.reply(res.data + "\n code:" + res.status);
        })
        .catch(error => {
            console.error(error);
        });
    }
    else if (commandName == 'lightoff') {
        axios
        .post('http://192.168.0.219/relay?relay2=off', {})
        .then(res => {
            interaction.reply(res.data + "\n code:" + res.status);
        })
        .catch(error => {
            console.error(error);
        });
    }
    else if (commandName == 'status') {
        axios
        .get('http://192.168.0.219/status', {})
        .then(res => {
            interaction.reply(res.data + "\n code:" + res.status);
        })
        .catch(error => {
            console.error(error);
        });
    }
});


// Login to Discord with your client's token
client.login(token);