# Schede di laboratorio Arduino: dai LED ai sensori

Tutto il codice del libro **_Schede di laboratorio Arduino – Dai LED ai sensori_** di Riccardo Annolfi:
27 progetti per imparare Arduino montando circuiti veri, dal primo LED al rover con due motori.

Non serve ricopiare niente dal libro: scarica il repository e apri lo sketch della scheda che stai facendo.

## Come scaricarlo

- **Senza installare niente:** in alto su questa pagina premi **Code → Download ZIP** e scompatta il file.
- **Con git:** `git clone https://github.com/RicAnn/schede-arduino-dai-led-ai-sensori.git`

## Come è organizzato

| Cartella | Che cosa contiene |
|---|---|
| `sketch/` | Un programma per cartella, pronto da aprire con l'**Arduino IDE** (File → Apri…) o da incollare in **Tinkercad** (Codice → Testo). |
| `wokwi/` | I progetti per il simulatore **[Wokwi](https://wokwi.com)**: `diagram.json` è il circuito già montato, `sketch.ino` il programma, `libraries.txt` le librerie da aggiungere. |

**Per usare un progetto Wokwi:** su wokwi.com crea un nuovo progetto **Arduino Uno**, poi nella scheda `diagram.json` cancella tutto e incolla il file della cartella; in `sketch.ino` incolla il programma; aggiungi le librerie elencate in `libraries.txt` dal Library Manager e premi ▶.

## Le schede

| N. | Scheda | Livello | Sketch | Wokwi |
|---|---|---|---|---|
| 1 | Il primo LED | Base | [es1_led/es1_led.ino](sketch/es1_led/es1_led.ino) | — |
| 2 | Pulsante e LED | Base | [es2_pulsante/es2_pulsante.ino](sketch/es2_pulsante/es2_pulsante.ino)<br>[es2b_interruttore/es2b_interruttore.ino](sketch/es2b_interruttore/es2b_interruttore.ino) | — |
| 3 | Potenziometro e luminosità | Base | [es3_potenziometro/es3_potenziometro.ino](sketch/es3_potenziometro/es3_potenziometro.ino) | — |
| 4 | Display a 7 segmenti | Intermedio | [es4_7segmenti/es4_7segmenti.ino](sketch/es4_7segmenti/es4_7segmenti.ino) | — |
| 5 | Display LCD 16×2 I²C | Intermedio | [es5_lcd_tinkercad/es5_lcd_tinkercad.ino](sketch/es5_lcd_tinkercad/es5_lcd_tinkercad.ino)<br>[es5_lcd_reale/es5_lcd_reale.ino](sketch/es5_lcd_reale/es5_lcd_reale.ino) | — |
| 6 | Display OLED 128×64 | Intermedio | [es6_oled/es6_oled.ino](sketch/es6_oled/es6_oled.ino) | [wokwi_es6_oled](wokwi/wokwi_es6_oled/) |
| 7 | Buzzer passivo | Base | [es7_buzzer_theremin/es7_buzzer_theremin.ino](sketch/es7_buzzer_theremin/es7_buzzer_theremin.ino)<br>[es7b_buzzer_melodia/es7b_buzzer_melodia.ino](sketch/es7b_buzzer_melodia/es7b_buzzer_melodia.ino) | — |
| 8 | Fotoresistenza | Base | [es8_fotoresistenza/es8_fotoresistenza.ino](sketch/es8_fotoresistenza/es8_fotoresistenza.ino) | — |
| 9 | Sensore di gas MQ-2 | Intermedio | [es9_gas/es9_gas.ino](sketch/es9_gas/es9_gas.ino) | [wokwi_es9_gas](wokwi/wokwi_es9_gas/) |
| 10 | Temperatura e umidità | Intermedio | [es10_dht/es10_dht.ino](sketch/es10_dht/es10_dht.ino)<br>[es10b_tmp36_tinkercad](sketch/es10b_tmp36_tinkercad/es10b_tmp36_tinkercad.ino) (Tinkercad) | [wokwi_es10_dht](wokwi/wokwi_es10_dht/) |
| 11 | Sensore a ultrasuoni | Intermedio | [es11_ultrasuoni/es11_ultrasuoni.ino](sketch/es11_ultrasuoni/es11_ultrasuoni.ino) | — |
| 12 | Sensore di movimento PIR | Base | [es12_pir/es12_pir.ino](sketch/es12_pir/es12_pir.ino) | — |
| 13 | Umidità del terreno | Base | [es13_terreno/es13_terreno.ino](sketch/es13_terreno/es13_terreno.ino) | — |
| 14 | Ricevitore IR e telecomando | Intermedio | [es14_telecomando/es14_telecomando.ino](sketch/es14_telecomando/es14_telecomando.ino) | [wokwi_es14_telecomando](wokwi/wokwi_es14_telecomando/) |
| 15 | Accelerometro e giroscopio | Avanzato | [es15_mpu6050/es15_mpu6050.ino](sketch/es15_mpu6050/es15_mpu6050.ino) | [wokwi_es15_mpu6050](wokwi/wokwi_es15_mpu6050/) |
| 16 | Sensore touch | Base | [es16_touch/es16_touch.ino](sketch/es16_touch/es16_touch.ino) | — |
| 17 | Sensori IR per il line follower | Intermedio | [es17_linea/es17_linea.ino](sketch/es17_linea/es17_linea.ino) | — |
| 18 | Joystick | Base | [es18_joystick/es18_joystick.ino](sketch/es18_joystick/es18_joystick.ino) | [wokwi_es18_joystick](wokwi/wokwi_es18_joystick/) |
| 19 | Sensore di tensione | Base | [es19_tensione/es19_tensione.ino](sketch/es19_tensione/es19_tensione.ino) | — |
| 20 | Cella di carico e HX711 | Intermedio | [es20_bilancia/es20_bilancia.ino](sketch/es20_bilancia/es20_bilancia.ino) | [wokwi_es20_bilancia](wokwi/wokwi_es20_bilancia/) |
| 21 | Sensore di polveri sottili | Avanzato | [es21_polveri/es21_polveri.ino](sketch/es21_polveri/es21_polveri.ino) | — |
| 22 | Encoder rotativo | Intermedio | [es22_encoder/es22_encoder.ino](sketch/es22_encoder/es22_encoder.ino) | [wokwi_es22_encoder](wokwi/wokwi_es22_encoder/) |
| 23 | Orologio RTC | Intermedio | [es23_rtc/es23_rtc.ino](sketch/es23_rtc/es23_rtc.ino) | [wokwi_es23_rtc](wokwi/wokwi_es23_rtc/) |
| 24 | Sensore laser ToF | Intermedio | [es24_tof/es24_tof.ino](sketch/es24_tof/es24_tof.ino) | — |
| 25 | Bumper con microswitch | Base | [es25_bumper/es25_bumper.ino](sketch/es25_bumper/es25_bumper.ino) | — |
| 26 | Motore DC e driver L298N | Intermedio | [es26_motore/es26_motore.ino](sketch/es26_motore/es26_motore.ino) | — |
| 27 | Il rover e la libreria Rover | Avanzato | [es27_rover](sketch/es27_rover/) | — |

## Licenza

Il **codice** di questo repository è rilasciato con licenza [MIT](LICENSE): puoi usarlo, modificarlo e condividerlo liberamente, anche in classe, citando l'autore.
I **testi e le illustrazioni** del libro restano © Riccardo Annolfi, tutti i diritti riservati.
