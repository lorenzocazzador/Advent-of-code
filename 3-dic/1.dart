import 'dart:io';

import 'dart:math';

List getSegments(List l) {
  Point precP = Point(0,0);
  List res = [];
  for(dynamic x in l) {
    String d = x.toString().substring(0,1);
    int v = int.parse(x.toString().substring(1));

    Point newPoint;
    switch(d) {
      case 'L':
        newPoint = Point(precP.x-v,precP.y);
        res.add([newPoint, precP]);
        break;
      case 'R':
        newPoint = Point(precP.x+v,precP.y);
        res.add([precP, newPoint]);
        break;
      case 'U':
        newPoint = Point(precP.x,precP.y+v);
        res.add([precP, newPoint]);
        break;
      case 'D':
        newPoint = Point(precP.x,precP.y-v);
        res.add([newPoint, precP]);
        break;
    }
    precP = newPoint;
  }
  return res;
}

int intersect(List s1, List s2) {
  String p1 = s1[0].x == s1[1].x ? 'py' : 'px',
         p2 = s2[0].x == s2[1].x ? 'py' : 'px';
  
  // if the 2 segments are parallel they don't intersect
  if(p1 == p2) 
    return -1;
  
  if(p1 == 'py' &&
     s1[0].y <= s2[0].y && s1[1].y >= s2[0].y && 
     s2[0].x <= s1[0].x && s2[1].x >= s1[0].x) {
       return s1[0].x.abs() + s2[0].y.abs();
  }
  else if(p1 == 'px' &&
    s1[0].x <= s2[0].x && s1[1].x >= s2[0].x &&
    s2[0].y <= s1[0].y && s2[1].y >= s1[0].y){
      return s1[0].y.abs() + s2[0].x.abs(); 
  }

  return -1;  
}

main() {
  List f = stdin.readLineSync().split(',');
  List s = stdin.readLineSync().split(',');

  List sf = getSegments(f), ss = getSegments(s);

  int res;
  for(int i=0; i<sf.length; i++) {
    List segF = sf[i];
    for(int j=0; j<ss.length; j++) {
      List segS = ss[j];

      if(segF[0] == Point(0,0) && segS[0] == Point(0,0))
        continue;
        
      int tmp = intersect(segF, segS);
      if(tmp != -1) 
        print(tmp);
      if(tmp != -1) 
        res = (res == null ? tmp : min(res, tmp));
    }
  }

  print('res --> $res');
}