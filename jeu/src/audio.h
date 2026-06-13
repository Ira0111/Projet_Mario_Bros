#ifndef AUDIO_H
#define AUDIO_H

#define BUZZER 25

int* currentMelody    = nullptr;
int* currentDurations = nullptr;
int  currentLength    = 0;
int  musicIndex       = 0;
bool musicPlaying     = false;
unsigned long nextNoteTime = 0;

extern int selectedLevel;

void initAudio() {
  pinMode(BUZZER, OUTPUT);
}

void updateAudio() {
  if (!musicPlaying) return;
  unsigned long now = millis();
  if (now < nextNoteTime) return;
  tone(BUZZER, currentMelody[musicIndex], currentDurations[musicIndex]);
  nextNoteTime = now + currentDurations[musicIndex] + 30;
  musicIndex   = (musicIndex + 1) % currentLength;
}

void playMusic(int* melody, int* durations, int length) {
  currentMelody    = melody;
  currentDurations = durations;
  currentLength    = length;
  musicIndex       = 0;
  musicPlaying     = true;
  nextNoteTime     = 0;
}

void stopMusic() {
  musicPlaying = false;
  noTone(BUZZER);
}

int menuMelody[] = { 440, 660, 880, 660 };
int menuDur[]    = { 200, 200, 200, 400 };

void playMenuMusic() { playMusic(menuMelody, menuDur, 4); }

int notesEasy[]   = { 440, 523, 587, 523, 440 };
int durEasy[]     = { 400, 300, 300, 300, 500 };
int notesNormal[] = { 440, 523, 587, 698, 659, 523 };
int durNormal[]   = { 250, 250, 300, 350, 400, 500 };
int notesHard[]   = { 880, 784, 880, 988, 880, 784, 659 };
int durHard[]     = { 150, 150, 150, 200, 150, 150, 300 };

void playLevelMusic() {
  switch (selectedLevel) {
    case 1: playMusic(notesEasy,   durEasy,   5); break;
    case 2: playMusic(notesNormal, durNormal, 6); break;
    case 3: playMusic(notesHard,   durHard,   7); break;
  }
}

inline void playValidateSound()    { tone(BUZZER, 700, 120); }

inline void playPortalTouchSound() {
  tone(BUZZER, 900, 120);
  delay(50);
  tone(BUZZER, 1200, 120);
}

inline void playDamageSound() {
  tone(BUZZER, 200, 80);
  delay(80);
  tone(BUZZER, 120, 120);
}

inline void playWinMusic() {
  tone(BUZZER, 880,  150); delay(150);
  tone(BUZZER, 988,  200); delay(200);
  tone(BUZZER, 1319, 300); delay(300);
}

inline void playGameOverMusic() {
  tone(BUZZER, 400, 200); delay(200);
  tone(BUZZER, 300, 200); delay(200);
  tone(BUZZER, 200, 400);
}
#endif