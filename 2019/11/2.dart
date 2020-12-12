import 'dart:collection';
import 'dart:io';
import 'dart:math';

int compare(Point a, Point b) {
  if(a.y != b.y)
    return a.y > b.y ? -1 : 1;
  else
    return a.x == b.x ? 0 : (a.x < b.x ? -1 : 1);
}

Map<int, int> m = {};
int relativeBase;
Point robot = Point(0,0);
SplayTreeMap<Point, int> points = SplayTreeMap(compare);
int verso = 0;

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
  int i = 0, output = 0;
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
      //print('op3, input: ');
      //int inp = int.parse(stdin.readLineSync());
      //print('letto');
      int inp = points.containsKey(robot) ? points[robot] : 0;

      String c = inp == 0 ? 'black' : 'white';
      //print(' $robot color: $c');
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
      if(output == 0) {
        //print(' paint $robot with $v1');
        points[robot] = v1;
      } else if(output == 1){
        String r = v1 == 0 ? 'left' : 'right';
        //print(' rotate $r');
        if(v1 == 0) {
          verso--;
          if(verso < 0)
            verso = 3;
        } else if(v1 == 1) {
          verso++;
          verso %= 4;
        }

        //if(verso == 0)
          //print(' go up');
        //else if(verso == 1)
          //print(' go right');
        //else if(verso == 2)
          //print(' go down');
        //else if(verso == 3)
          //print(' go left');

        if(verso == 0)
          robot = Point(robot.x, robot.y+1);
        else if(verso == 1)
          robot = Point(robot.x+1, robot.y);
        else if(verso == 2)
          robot = Point(robot.x, robot.y-1);
        else if(verso == 3)
          robot = Point(robot.x-1, robot.y);
        else print('ERROR: verso=$verso not in range [0,3]');
      }
      output++;
      output %= 2;
      i += 2;
    } else if(op == 5) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2);

      //print(' $v1 $v2');
      if(v1 != 0)
        i = v2;
      else i += 3;
    } else if(op == 6) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2);

      //print(' $v1 $v2');

      if(v1 == 0)
        i = v2;
      else i += 3;
    } else if(op == 7) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);

      //print(' $v1 $v2 $v3');

      if(v1 < v2)
        m[v3] = 1;
      else
        m[v3] = 0;

      i += 4;
    } else if(op == 8) {
      int v1 = getValue(p1, i+1),
          v2 = getValue(p2, i+2),
          v3 = (p3 == 0 ? m[i+3] : m[i+3]+relativeBase);


      //print(' $v1 $v2 $v3');

      if(v1 == v2)
        m[v3] = 1;
      else
        m[v3] = 0;

      i += 4;
    } else if(op == 9) {
      int v1 = getValue(p1, i+1);

      relativeBase += v1;

      //print(' $v1 newRelativebase: $relativeBase');
      i += 2;
    } else if(op == 99) {
      //print(' break');
      break;
    }
  }

  return;
}

main() async {
  //List<int> l = stdin.readLineSync().split(',').map(int.parse).toList();
  String file = await File('input/in').readAsString();
  List<int> l = file.split(',').map(int.parse).toList();

  print('LENGTH INTCODE: ${l.length}');
  for(int i=0; i<l.length; i++)
    m[i] = l[i];

  points[Point(0,0)] = 1;
  intcode_computer(m.length);

  print('points colorated --> ${points.keys.length}');

  int offsetY = 0, maxY = -10000, offsetX = 0, maxX = -10000;
  points.forEach( (p, c){
    offsetX = min(offsetX, p.x);
    maxX = max(maxX, p.x);
    offsetY = min(offsetY, p.y);
    maxY = max(maxY, p.y);
  });
  offsetY = offsetY.abs();
  offsetX = offsetX.abs();

  List<List<String>> res = [];
  for(int i=0; i<=maxY+offsetY; i++) {
    res.add([]);
    for(int j=0; j<=maxX+offsetX; j++)
      res[i].add(' ');
  }

  points.forEach( (p,c) {
    res[p.y+offsetY][p.x+offsetX] = c == 1 ? '#' : ' ';
  });

  for(int i = res.length-1; i >= 0; i--) {
    for(String s in res[i])
      stdout.write(s);
    print('');
  }
}
