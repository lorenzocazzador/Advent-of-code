/*
  The code is the same of 9-dic/1.dart
  The only difference is the "op3 input" to give to the 2 programs:
  "1", which stands for 'test mode',  for the part one and
  "2", which stands for 'boost mode', for the part two
*/

import 'dart:io';

Map<int, int> m = {};
int relativeBase;

int getM(int index) {
  if(m.containsKey(index))
    return m[index];
  else 
    return m[index] = 0;
}

int getValue(int parameterMode, int index) {
  int res = -1;

  if(parameterMode == 0)
    res = getM(getM(index));
  else if(parameterMode == 1)
    res = getM(index);
  else if(parameterMode == 2)
    res = getM(getM(index)+relativeBase);
  else print('ERROR: parameterMode=$parameterMode not implemented');

  return res;
}

void intcode_computer(int length) {
  int i = 0;
  relativeBase = 0;

  while(i < length) {
    int op = m[i] % 100, p1 = m[i] ~/ 100 % 10, p2 = m[i] ~/ 1000 % 10, p3 = m[i] ~/ 10000 % 10;
    if(op == 1) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);

      m[v3] = v1 + v2;
      i+=4;
    } else if(op == 2) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);

      m[v3] = v1 * v2;
      i+=4;
    } else if(op == 3) {
      print('op3, input: ');
      int inp = int.parse(stdin.readLineSync());
      print('letto');

      int index;
      if(p1 == 0)
        index = m[i+1];
      else if(p1 == 2)
        index = m[i+1]+relativeBase;
      else print('ERROR parameterMode not accepted i -> $i m[i] -> ${m[i]}');

      m[index] = inp;
      i += 2;
    } else if(op == 4) {
      int v1 = getValue(p1, i+1);
      //print('op4: i --> $i l2[i] -> ${l2[i]}');
      print('op4: $v1');
      i += 2;
    } else if(op == 5) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2);
      if(v1 != 0)
        i = v2;
      else i += 3;
    } else if(op == 6) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2);
      if(v1 == 0)
        i = v2;
      else i += 3;
    } else if(op == 7) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);

      if(v1 < v2)
        m[v3] = 1;
      else 
        m[v3] = 0;   

      i += 4;   
    } else if(op == 8) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);

      if(v1 == v2)
        m[v3] = 1;
      else
        m[v3] = 0;

      i += 4;
    } else if(op == 9) {
      int v1 = getValue(p1, i+1);

      relativeBase += v1;
      i += 2;
    } else if(op == 99) 
      break;
  }

  return;
}

main() {
  List<int> l = stdin.readLineSync().split(',').map(int.parse).toList();

  for(int i=0; i<l.length; i++) 
    m[i] = l[i];

  intcode_computer(l.length);
}