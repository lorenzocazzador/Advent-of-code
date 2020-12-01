import 'dart:io';
import 'dart:math';

List<Point> l = [];

int solve(Point p) {
  Map<double, List<bool>> m = {}; 
  for(Point x in l) {
    if(x != p) {
      bool up = (x.y != p.y ? x.y > p.y : x.x > p.x);
      double slope = (p.x-x.x)/(p.y-x.y);
      
      if(!m.containsKey(slope))
        m[slope] = [false, false];

      if(up)
        m[slope][0] = true;
      else 
        m[slope][1] = true;
    }
  }
  //print(s);
  int res = 0;
  m.forEach((d, l) {
    res += (l[0] ? 1 : 0) + (l[1] ? 1 : 0);
  });
  return res;
}

main() {
  int i=0;
  while(true) {
    String s = stdin.readLineSync();

    if(s == '')
      break;

    for(int j=0; j<s.length; j++)
      if(s[j] == '#')
        l.add(Point(j,i));
    i++;
  }

  int res = 0;
  for(Point p in l)
    res = max(res, solve(p));

  print('res --> $res');
}