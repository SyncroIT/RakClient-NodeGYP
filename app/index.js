const { connect } = require('./build/Debug/samp');
connect(message);

function message(msg) {
    console.log('JAVASCRIPT MSG', msg);
}
