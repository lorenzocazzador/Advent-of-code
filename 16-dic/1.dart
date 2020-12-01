import 'dart:io';

int nPhases = 100;
List<int> basePattern = [0,1,0,-1];

class Pattern {
  int ind, v;

  Pattern(this.ind, this.v);

  String toString() {
    return '(' + ind.toString() + ',' + v.toString() + ')';
  }
}

List<Pattern> getPattern(int ind, int length) {
  ind++;
  List<Pattern> pattern = [];
  int ip = 0, il = 0, it = 0;
  while(it < length+1) {
    if(il == ind) {
      il = 0;
      ip++; ip %= 4;
    }
    if(basePattern[ip] != 0)
      pattern.add(Pattern(it-1, basePattern[ip]));
    il++;
    it++;
  }

  return pattern;
}

List<int> runPhase(List<int> input) {
  List<int> output = [];

  for(int i=0; i<input.length; i++) {
    List<Pattern> p = getPattern(i, input.length);
    int tmp = 0;
    for(Pattern p2 in p)
      tmp += input[p2.ind] * p2.v;
    tmp = tmp.abs();
    output.add(tmp%10);
  }

  return output;
}

main() async {
  String s = await File('16-dic/in').readAsString();

  List<int> input = [];
  
  for(int i=0; i<s.length; i++)
    input.add(int.parse(s[i]));

  for(int i=0; i<nPhases; i++) 
    input = runPhase(input);

  for(int i=0; i<8; i++)
    stdout.write(input[i]);


  //for(int i=0; i<8; i++)
    //print('$i -> ${getPattern(i, 8)}');
}