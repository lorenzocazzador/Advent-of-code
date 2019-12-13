/*
  The code is the same of 9-dic/1.dart
  The only difference is the "op3 input" to give to the 2 programs:
  "1", which stands for 'test mode',  for the part one and
  "2", which stands for 'boost mode', for the part two
*/

import 'dart:collection';
import 'dart:io';

import 'dart:math';

int compare(Point a, Point b) {
  if(a.y != b.y)
    return a.y < b.y ? -1 : 1;
  else 
    return a.x == b.x ? 0 : (a.x < b.x ? -1 : 1);
}

Map<int, int> m = {};
int relativeBase;
SplayTreeMap<Point, int> points = SplayTreeMap(compare);
Point paddle, ball, dirBall = Point(1,1), posPrec, np;
File out = File('13-dic/out');
String joystickMoves;

void printTable() {
  int offsetX = 0, maxX = -100000, offsetY = 0, maxY = -100000;
  points.forEach( (p, t) {
    offsetX = min(offsetX, p.x);
    maxX = max(p.x, maxX);
    offsetY = min(offsetY, p.y);
    maxY = max(p.y, maxY);
  });
  offsetX = offsetX.abs();
  offsetY = offsetY.abs();
  List<List<String>> table = [];
  for(int i=0; i<=maxY+offsetY; i++) {
    List<String> tmp = [];
    for(int j=0; j<=maxX+offsetX; j++) {
      tmp.add('.');
    }
    table.add(tmp);
  }

  points.forEach((p, t){
    String s;

    if(t == 0) s = ' ';
    if(t == 1) s = '#';
    else if(t == 2) s = '*';
    else if(t == 3) s = '-';
    else if(t == 4) s = '@';
    
    //print('x: ${maxX+offsetX}');
    table[p.y][p.x] = s;
  });

  for(int i=0; i<table.length; i++) {
    for(int j=0; j<table[i].length; j++)
      stdout.write(table[i][j]);
    print('');
  }
}

Point findBallNextPos() {
  Point nextPos = ball;
  //stdout.write('1: ${ball.y},${paddle.y}\n');
  if(ball.y >= paddle.y) {
    printTable();
    int d = (ball.x-paddle.x).abs();
    print('dist: ${d-1}');
  } else {
    while(nextPos.y+1 != paddle.y) {
      Point sx = Point(nextPos.x-1, nextPos.y);
      if(points[sx] == 1)
        dirBall = Point(-dirBall.x, dirBall.y);
      
      Point dx = Point(nextPos.x+1, nextPos.y);
      if(points[dx] == 1)
        dirBall = Point(-dirBall.x, dirBall.y);

      Point down = Point(nextPos.x, nextPos.y+1);
      if(points[down] == 2)
        return null;

      Point up = Point(nextPos.x, nextPos.y-1);
      if(points[up] == 1)
        dirBall = Point(dirBall.x, -dirBall.y);

      nextPos = Point(nextPos.x + dirBall.x, nextPos.y + dirBall.y);
    }
  }
  //print('2');
  return nextPos;
}

int count() {
  int count = 0;
  points.forEach((p, t){ if(t == 2)count++;});
  return count;
}
int lol=0;
void findPaddleAndBall() {
  posPrec = ball;
  points.forEach((p, t){
    if(t == 3)
      paddle = p;
    else if(t == 4)
      ball = p;
  });
  if(posPrec != null && (ball.y == posPrec.y+1 || ball.y == posPrec.y-1)) {
    dirBall = Point(ball.x-posPrec.x,ball.y-posPrec.y);
    np = findBallNextPos();
    int cnt = count();
    //if(cnt == 1) print('np $np');
    if(np == Point(9,21) && cnt == 1) {
      if(lol == 24) printTable();
      lol++;
    }
  } else np = null;
}



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
  
  int i = 0, output = 0, x, y, indexMoves = 0;
  relativeBase = 0;
  bool firstInput = false;

  while(i < length) {
    int op = m[i] % 100, p1 = m[i] ~/ 100 % 10, p2 = m[i] ~/ 1000 % 10, p3 = m[i] ~/ 10000 % 10;
    //print('op: $op');
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
      int inp = 0;

      if(indexMoves < joystickMoves.length) {
        String move = joystickMoves[indexMoves];
        inp = move == '-' ? 0 : (move == '<' ? -1 : 1); 
        do{
          indexMoves++;
        }while(indexMoves < joystickMoves.length && joystickMoves[indexMoves] == '@');
      } else {
        /*if(!firstInput){
          printTable();
        } else if(ball.y+1 == paddle.y && ball.x == paddle.x) {
          out.writeAsStringSync('@', mode: FileMode.append);
        }
        int byte;
        if(paddle.y-ball.y >= 7)
          byte = 50;
        else {
          firstInput = true; 
          print('op3, input: ');
          stdin.lineMode = false;
          byte = stdin.readByteSync();
        }
        if(byte == 50) {
          inp = 0;
          out.writeAsStringSync('-', mode: FileMode.append);
        } else if(byte == 52) {
          inp = -1;
          out.writeAsStringSync('<', mode: FileMode.append);
        } else if(byte == 54) {
          inp = 1;
          out.writeAsStringSync('>', mode: FileMode.append);
        }*/
        if(!firstInput)
          printTable();
        firstInput = true;
        if(np == null || paddle.x == np.x) {
          inp = 0;
          out.writeAsStringSync('-', mode: FileMode.append);
        } else if(np.x < paddle.x){
          inp = -1;
          out.writeAsStringSync('<', mode: FileMode.append);
        } else if(np.x > paddle.x) {
          inp = 1;
          out.writeAsStringSync('>', mode: FileMode.append);
        }
        //int inp = int.parse(stdin.readLineSync());
        //print('letto');
      }

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
      //print('op4: $v1');
      if(output == 0)
        x = v1;
      else if(output == 1)
        y = v1;
      else if(output == 2) {
        if(x == -1 && y == 0) {
          print('$x,$y,$v1');
        }else {
          points[Point(x,y)] = v1;
          findPaddleAndBall();
          //if(firstInput) printTable();
        }
      }
      
      output++;
      output %= 3;
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

main() async {
  String file = await File('13-dic/in').readAsString();
  joystickMoves = await out.readAsString();
  List<int> l = file.split(',').map(int.parse).toList();

  l[0] = 2;
  for(int i=0; i<l.length; i++) 
    m[i] = l[i];

  print('length: ${l.length}');  
  intcode_computer(l.length);



  //print('res --> $res');
}
