#define note_C 1E6/1046
#define note_E 1E6/1319
#define note_F 1E6/1397
#define note_G 1E6/1568
#define note_A 1E6/1760
#define note_B 1E6/1865

void attackChirp() {
	for ( int i = 0; i < 3; i++ ) {
		Piezo::chirp( 1E6/1500, 1E6/1900, 8 );
	}
}

void playWeddingMelody()
{
	LEDs::glow();
	Piezo::on();
	attackChirp();
	Piezo::chirp( 1E6/2000, note_C, 8 );
	Piezo::tone( note_C, 1E6*0.4 );
	LEDs::off();
	delay( 100 );
	Piezo::chirp( 1E6/1000, note_F, 8 );
	Piezo::tone( note_F, 1E6*0.3 );
	delay( 50 );
	Piezo::tone( note_F, 1E6*0.1 );
	delay( 80 );
	LEDs::glow();
	Piezo::chirp( 1E6/1800, note_F, 8 );
	Piezo::tone( note_F, 1E6*0.5 );
	Piezo::off();
	LEDs::off();
	delay( 600 );
	LEDs::glow();
	Piezo::on();
	attackChirp();
	Piezo::chirp( 1E6/2000, note_C, 8 );
	Piezo::tone( note_C, 1E6*0.4 );
	LEDs::off();
	delay( 100 );
	Piezo::chirp( 1E6/1000, note_G, 8 );
	Piezo::tone( note_G, 1E6*0.3 );
	delay( 50 );
	Piezo::tone( note_E, 1E6*0.1 );
	delay( 80 );
	LEDs::glow();
	Piezo::chirp( 1E6/1800, note_F, 8 );
	Piezo::tone( note_F, 1E6*0.5 );
	Piezo::off();
	LEDs::off();
	delay( 600 );
	LEDs::glow();
	Piezo::on();
	attackChirp();
	Piezo::chirp( 1E6/2000, note_C, 8 );
	Piezo::tone( note_C, 1E6*0.4 );
	LEDs::off();
	delay( 100 );
	LEDs::glow();
	Piezo::chirp( 1E6/1000, note_F, 8 );
	Piezo::tone( note_F, 1E6*0.3 );
	LEDs::off();
	delay( 60 );
	LEDs::glow();
	Piezo::chirp( 1E6/2000, note_F, 8 );
	Piezo::tone( note_B, 1E6*0.1 );
	LEDs::off();
	delay( 40 );
	LEDs::glow();
	Piezo::chirp( note_F, note_B, 8 );
	Piezo::tone( note_B, 1E6*0.5 );
	LEDs::off();
	delay( 80 );
	LEDs::glow();
	Piezo::chirp( note_F, note_A, 8 );
	Piezo::tone( note_A, 1E6*0.3 );
	LEDs::off();
	delay( 20 );
	Piezo::tone( note_G, 1E6*0.2 );
	delay( 30 );
	LEDs::glow();
	attackChirp();
	Piezo::chirp( 1E6/2000, note_F, 8 );
	Piezo::tone( note_F, 1E6*0.35 );
	LEDs::off();
	delay( 30 );
	Piezo::tone( note_F, 1E6*0.15 );
	delay( 20 );
	LEDs::glow();
	Piezo::chirp( 1E6/1000, note_E, 8 );
	Piezo::tone( note_E, 1E6*0.25 );
	Piezo::tone( note_F, 1E6*0.3 );
	LEDs::off();
	Piezo::chirp( note_E, note_G, 8 );
	LEDs::glow();
	Piezo::tone( note_G, 1E6*0.5 );
	Piezo::off();
	LEDs::off();
}
