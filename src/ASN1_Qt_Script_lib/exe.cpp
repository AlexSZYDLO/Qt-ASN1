#include <QCoreApplication>
#include <iostream>

#include "Script.h"

const QString script1(); // bitstring
const QString script2(); // utc time
const QString script3(); // sequence
const QString script4(); // sequence of
const QString script5(); // choice
const QString script6(); // set

int main(int argc, char const *argv[])
{
  std::cout << "/* start */" << std::endl;
  QCoreApplication app(argc, const_cast<char **>(argv));
  QString error;
  bool res = true;
  bool all = false;

  if (false || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script1(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cBitString;
    res &= eng->globalObject().property("s").toString().toStdString() == "";

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "0300";
  }

  if (false || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script2(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cUTCTime;
    res &= eng->globalObject().property("s1").toString().toStdString() == "9001031702+0100";
    res &= eng->globalObject().property("s2").toString().toStdString() == "9103111030+0100";

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "170F393130333131313033302B30313030";
  }

  if (false || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script3(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cSequence;

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "AA080A0204A00C020520";
  }

  if (false || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script4(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cSequenceOf;

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "CC0D030200FF030200C3030303FF00";
  }

  if (false || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script5(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cChoice;
    res &= eng->globalObject().property("s").toString().toStdString() == "3.14";

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) == "AA030B0103";
  }

  if (true || all)
  {
    QJSEngine *eng = InitEngine();
    std::shared_ptr<ASN1_Object> obj = GrammarFromScript(eng, script6(), error);
    res &= error.isEmpty();
    res &= obj->GetType() == Utils::eNodeType::cSet;

    ClearScriptEngine(eng);

    ByteArray buffer;
    obj->WriteIntoBuffer(buffer);
    res &= std::string(buffer.GetString()) ==
    "BB6C0A01FF0B0104BFB90009616C6578616E6472650D02E69C0F085CFA10866B0184711A1000112233445566778899AABBCCDDEEFF1B09"
    "80D6082D4CCCCCCCCD1C0F393030313033313730322B303130301D0F393130333131313033302B303130301E0A737A79646C6F77736B69";
  }

  ClearGrammar();
  res &= ScriptMemoryCheck();

  std::cout << "/* done */ " << (res ? "OK" : "NOT OK !!!") << std::endl;
  return 0;
}

// Scripts

const QString script6()
{
  return R"(
  var a = new BooleanASN1('bool', '0A');
  var b = new EnumeratedASN1('enum', '0B');
  var c = new IA5StringASN1('ia5 string', 'BFB900');
  var d = new IntegerASN1('integer a', '0D');
  var e = new NullASN1('null', '0E', true);
  var f = new ObjectIDASN1('OID', '0F');
  var g = new OctetStringASN1('octet string', '1A');
  var h = new RealASN1('real', '1B');
  var i = new UTCTimeASN1('utc time', '1C');
  var j = new UTCTimeASN1('utc time', '1D');
  var k = new UTF8StringASN1('utf8 string', '1E');

  var arr = [a, b, c, d, e, f, g, h, i, j, k];
  var set1 = new SetASN1(arr, 'set 1', 'BB');
  set1.registerGrammar();

  a.setBooleanValue(true);
  b.setEnumeratedValue(4);
  c.setIA5StringValue("alexandre");
  d.setIntegerValue(-6500);
  e.setIgnoredByUser();
  f.setObjectIDValue("2.12.15632.875.1.625");
  g.setOctetStringValue("00112233445566778899aabbccddeeff");
  h.setRealValue("523.325");
  i.setUTCTimeValue("9001031702+0100");
  j.setUTCTimeValue(91, 3, 11, 10, 30, 0, UTCTimeASN1.Plus, 1, 0);
  k.setUTF8StringValue("szydlowski");
)";
}

const QString script5()
{
  return R"(
  var chCallBack = function(i) {
      if (i === 0) return new BitStringASN1('bitstring c1', '0A');
      if (i === 1) return new IntegerASN1('int c2', '0B');
      if (i === 2) return new RealASN1('real c3', '0C');
      if (i === 3) return new OctetStringASN1('octet string c4', '0D');
  }

  var ch1 = new ChoiceASN1(chCallBack, 7, 'theChoice', 'AA');
  ch1.registerGrammar();

  ch1.setSelectedChoice(2).setRealValue(3.14);
  var s = ch1.getSelectedChoice().getRealValue();
  ch1.setSelectedChoice(1).setIntegerValue(3);
)";
}

const QString script4()
{
  return R"(
  var seqofcallback = function() {
    return new BitStringASN1('seqof bitstring');
  }

  var seqof = new SequenceOfASN1(seqofcallback, 'sequence of', 'CC');
  seqof.registerGrammar();

  seqof.appendNewObject().setBitStringValue('11111111');
  seqof.appendNewObject().setBitStringValue('11000011');
  seqof.appendNewObject().setBitStringValue('1111111100000');
  seqof.deleteObjectAt(2);
  seqof.appendNewObject().setBitStringValue('1111111100000');
)";
}

const QString script3()
{
  return R"(
  function MakeSeq1() {
    var a1 = new BitStringASN1('bitstring a', '0A');
    var b1 = new BitStringASN1('bitstring b', '0B', true, true);
    var c1 = new BitStringASN1('bitstring c', '0C');
    return [a1, b1, c1];
  }

  var seq1 = new SequenceASN1(MakeSeq1(), 'Sequence 1', 'AA');
  seq1.registerGrammar();

  seq1.getObjectAt(0).setBitStringValue('1010');
  seq1.getObjectAt(1).setBitStringValue('1000');
  seq1.getObjectAt(1).setIgnoredByUser(true);
  seq1.getObjectAt(2).setBitStringValue('001');
)";
}

const QString script2()
{
  return R"(
  var A = new UTCTimeASN1('T');
  A.registerGrammar();

  A.setUTCTimeValue("9001031702+0100");
  var s1 = A.getUTCTimeValue();

  A.setUTCTimeValue(91, 3, 11, 10, 30, 0, UTCTimeASN1.Plus, 1, 0);
  var s2 = A.getUTCTimeValue();
)";
}

const QString script1()
{
  return R"(
  var defA = new BitStringASN1('def A');
  defA.setBitStringValue('11');

  var A = new BitStringASN1('A', '', false, false, defA);
  A.registerGrammar();

  var s = A.getBitStringValue();
)";
}
