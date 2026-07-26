/*
  ===========================================================
  التاسك: تحريك 4 محركات سيرفو (Servo Motors) بحركتين بالترتيب
  1) حركة Sweep (يمين ويسار) لمدة ثانيتين فقط.
  2) بعد انتهاء الثانيتين: توقف كل المحركات وتثبت عند زاوية 90 درجة.

  البرنامج: Tinkercad Circuits (محاكاة Arduino Uno)
  ===========================================================
*/

#include <Servo.h>

// إنشاء 4 كائنات Servo لكل محرك
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// أرقام البنات (Pins) اللي متوصل فيها كل سيرفو
// ملاحظة: نستخدم بنات PWM (فيها ~) عشان تتحكم بدقة بزاوية السيرفو
const int PIN_SERVO1 = 3;
const int PIN_SERVO2 = 5;
const int PIN_SERVO3 = 6;
const int PIN_SERVO4 = 9;

// مدة حركة الـ Sweep بالمللي ثانية (2 ثانية = 2000 مللي ثانية)
const unsigned long SWEEP_DURATION = 2000;

// دالة تكتب نفس الزاوية على كل المحركات الأربعة دفعة وحدة
void writeAllServos(int angle) {
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);
  servo4.write(angle);
}

void setup() {
  // Serial للمتابعة (اختياري - يفيد وقت التجربة)
  Serial.begin(9600);

  // ربط كل سيرفو بالبن الخاص فيه
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  servo3.attach(PIN_SERVO3);
  servo4.attach(PIN_SERVO4);

  Serial.println("بدء حركة Sweep لمدة ثانيتين...");

  // ---------------------------------------------------------
  // الحركة الأولى: Sweep (يمين ويسار) لمدة ثانيتين بالضبط
  // ---------------------------------------------------------
  unsigned long startTime = millis();
  bool timeUp = false;

  while (!timeUp) {
    // الحركة من 0 إلى 180 درجة
    for (int pos = 0; pos <= 180 && !timeUp; pos++) {
      writeAllServos(pos);
      delay(15); // تأخير بسيط عشان الحركة تكون سلسة
      if (millis() - startTime >= SWEEP_DURATION) {
        timeUp = true;
      }
    }

    // الحركة الرجوع من 180 إلى 0 درجة
    for (int pos = 180; pos >= 0 && !timeUp; pos--) {
      writeAllServos(pos);
      delay(15);
      if (millis() - startTime >= SWEEP_DURATION) {
        timeUp = true;
      }
    }
  }

  // ---------------------------------------------------------
  // الحركة الثانية: تثبيت كل المحركات عند 90 درجة
  // ---------------------------------------------------------
  Serial.println("انتهت الثانيتين - تثبيت المحركات عند 90 درجة");
  writeAllServos(90);
}

void loop() {
  // ما نسوي شي هنا - المحركات تبقى ثابتة عند 90 درجة
  // (تكرار الأمر لضمان ثبات الزاوية بدون أي أثر على الحركة)
  writeAllServos(90);
}
