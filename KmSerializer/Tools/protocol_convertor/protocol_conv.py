#!/usr/bin/env python
# -*- coding: utf-8 -*-
import re
import os
import sys
import xlrd
import codecs
import csv
import time
import copy
from jinja2 import Environment, FileSystemLoader


# jinja2 Documentation
# http://jinja.pocoo.org/docs/2.9/

#컨버터용 파라미터
_include=[]
_include_sub=[]
_filepath=[]
_filename=[]

_filepath_cpp = []
_filepath_cs = []
_classname = []    #$$ array로 할 이유가 없다.
_member=[]
_response_originalclass =[]
_request_originalclass = []
_originalclass = []
_ifdef=[]
_define=[]
_type_cpp=[]
_type_cs=[]
_request_member = []
_response_member =[]
_request_type = []
_response_type = []

_request_type_cpp = []
_response_type_cpp = []

_request_type_cs = []
_response_type_cs = []

# 주석 삽입
_comment_member = []
_comment_class = []
_comment_type = ''
_comment_member_request = []
_comment_member_response = []

# 레이아웃용
_layout_maxreq_typelen = 0
_layout_maxreq_varname = 0
_layout_maxres_typelen = 0
_layout_maxres_varname = 0

# PacketID
_packet_ids = {}

# [request, response, notify, inner] 가 들어감
_signal_type = ''

# 클래스의 유무 탐색용
_class_sumarry = []

_TYPE_SUMARRY = ['char','unsigned char','short',
'unsigned short','int',
'unsigned int','long','unsigned long',
'float','double','long double','bool','string','binary']

_PARAM_SUMARRY = ['filepath','classname','member','inner']

#_TEMPLATE_FILE =['template.cpp','template_cpp.h','template.cs','template_inner.cs','template_inner.cpp','template_inner.h']
_TEMPLATE_FILE =['template_packet.cpp','template_packet.h','template_packet.cs','template_inner.cs','template_inner.cpp','template_inner.h']
_TEMPLATE_DIR = './template'

def set_class_name(book):
    #sheet = book.sheet_by_index(sheets)
    for s in range(book.nsheets):
        sheet_name = book.sheet_by_index(s).name
        sheet = book.sheet_by_index(s)
        for row in range(sheet.nrows):
            value = get_cell_string(sheet,row,1)
            if value == '' or sheet_name =='common':
                continue
            if value == 'classname':
                class_name = get_cell_string(sheet,row,2)
                if class_name == '':
                    sys.stderr.write('classname of null')
                    return
                p = re.compile('\w')
                result = p.findall(class_name)
                if len(class_name) != len(result):
                    sys.stderr.write(u'classnameType error ')
                    return
                setparam('class_sumarry',class_name.lower())
    print u'\n클래스 수\n'
    print len(_class_sumarry)





def convert_protocol(excel_file):
    book = xlrd.open_workbook(excel_file)
    print u"시트 수"
    print book.nsheets
   #シートのクラスを取得
    set_class_name(book)

    for sheets in range(book.nsheets):
        sheet_name = book.sheet_by_index(sheets).name
        sheet = book.sheet_by_index(sheets)


        column = 0
        for row in range(sheet.nrows):
            cell_v1 = get_cell_string(sheet,row,column)
            if cell_v1 == "common":
                search_cell_value(sheet,row,sheet_name)
            if cell_v1 == '#':
                search_cell_value(sheet,row,sheet_name)
                file_write_cs()
                file_write_cpp()


def search_cell_value(sheet,startrow,sheet_name):
    #パラメータのクリア
    clear_param()
    columns =1
    for rows in range(startrow,sheet.nrows):
        cell_value1 = get_cell_string(sheet,rows,columns)
        if get_cell_string(sheet,rows,0) != '':
                    set_signal_type(get_cell_string(sheet,rows,0))
        if check_param(cell_value1):
            if cell_value1 != "":
                cell_value2 = get_cell_string(sheet,rows,columns+1)
                if cell_value2 != "":
                    #パラメータがmember
                    if cell_value1 == 'member':

                        if check_type(cell_value2):
                            if check_existence_class(replace_parentheses(cell_value2)):
                                if check_original_class(cell_value2):
                                #共通クラス時にファイルのインクルードと変数宣言を追加
                                    setparam('originalclass',replace_parentheses(cell_value2))
                                #インクルード
                                    setparam('include_sub',replace_parentheses(cell_value2).lower()+'.h')
                            else :
                                continue
                        set_comment_type(cell_value1)
                        setparam("comment", get_cell_string(sheet,rows,columns+4) )
                        if get_cell_string(sheet,rows,columns+2) != "":
                            setparam('member',get_cell_string(sheet,rows,columns+2))
                        else:
                            sys.stderr.write('input cell D')

                        setparam('type',cell_value2)
                    elif cell_value1 == 'classname':
                        set_comment_type(cell_value1)
                        global _comment_type
                        setparam("comment", get_cell_string(sheet,rows,columns+4) )

                        #ifdef,defineの文字列生成
                        setparam('classname',cell_value2)
                        setparam('ifdef',createstring(cell_value2))
                        setparam('define',createstring(cell_value2))
                    elif cell_value1 == 'filepath':
                        setparam('filepath',cell_value2)
                else :
                    sys.stderr.write('Forget input in cell C\n' )
            if cell_value1 == "" and get_cell_string(sheet,rows-1,columns) != "" :
                return
        else:
            return

def file_write_h(language):
    global _signal_type
    env = Environment(loader = FileSystemLoader(_TEMPLATE_DIR, encoding='utf-8'),
        autoescape = False)

    # template_inner.h
    if _signal_type == 'inner':
        tmpl_inner_h = env.get_template(_TEMPLATE_FILE[5])
        fout_inner_h = open(_filepath_cpp[0]+"/common/"+_classname[0].lower()+'.h',"wb")
        fout_inner_h.write(tmpl_inner_h.render(param=sendparam(language)).encode("utf-8"))
        fout_inner_h.close
        return

    # template_cpp.h
    tmpl_h = env.get_template(_TEMPLATE_FILE[1])
    fout_h = codecs.open(_filepath_cpp[0]+"/"+_classname[0].lower()+'.h',"wb","utf-8")
    fout_h.write(tmpl_h.render(param=sendparam(language)))
    fout_h.close

def file_write_cpp():
    env = Environment(loader = FileSystemLoader(_TEMPLATE_DIR, encoding='utf-8'),autoescape = False)
    global _signal_type
    file_write_h('cpp')
    setparam('include',_classname[0].lower()+'.h')
    #共通クラス
    if _signal_type == 'inner':
        # template_inner.cpp
        tmpl_inner_cpp = env.get_template(_TEMPLATE_FILE[4])
        fout_inner_cpp = open(_filepath_cpp[0]+"/common/"+_classname[0].lower()+'.cpp',"wb")
        fout_inner_cpp.write(tmpl_inner_cpp.render(param=sendparam('cpp')).encode("utf-8"))
        fout_inner_cpp.close
        return

    # template.cpp
    tmpl_cpp = env.get_template(_TEMPLATE_FILE[0])
    fout_cpp = codecs.open(_filepath_cpp[0]+"/"+_classname[0].lower()+'.cpp',"wb","utf-8")
    fout_cpp.write(tmpl_cpp.render(param=sendparam('cpp')))
    fout_cpp.close


def file_write_cs():
    file_write_h('cs')
    env = Environment(loader = FileSystemLoader(_TEMPLATE_DIR, encoding='utf-8'),
        autoescape = False)
    env.filters['camel_to_pascal'] = camel_to_pascal
    #共通クラス生成
    global _signal_type
    if _signal_type == 'inner':
        # template_inner.cs
        tmpl_inner_cs = env.get_template(_TEMPLATE_FILE[3])
        fout_inner_cs = open(_filepath_cs[0]+"/Param/"+camel_to_pascal(_classname[0])+'.cs',"w")
        fout_inner_cs.write(tmpl_inner_cs.render(param=sendparam('cs')).encode("utf-8-sig"))
        fout_inner_cs.close
    else :
        # template.cs
        tmpl_cs = env.get_template(_TEMPLATE_FILE[2])
        fout_cs = open(_filepath_cs[0]+"/"+camel_to_pascal(_classname[0])+'.cs',"w")
        fout_cs.write(tmpl_cs.render(param=sendparam('cs')).encode("utf-8-sig"))
        fout_cs.close


def FileWritePacketID():
    env = Environment(loader = FileSystemLoader(_TEMPLATE_DIR, encoding='utf-8'),
        autoescape = False)
    #
    tmpl_h = env.get_template( 'template_packetid.h' )
    fout_h = codecs.open(_filepath_cpp[0]+"/" + 'PktID' +'.h',"wb","utf-8")
    fout_h.write( tmpl_h.render(param=SendParamForPacketID()) )
    fout_h.close



def check_param(value):
    for sumarry in _PARAM_SUMARRY:
        if sumarry == value:
            return True
    if value != "":
        sys.stderr.write('param input error => %s\n'% value)
    return False


#클래스명의 첫글자를 대문자로 한다(ex.XxxxXxxx)
def convert_classname(value):
    result = []
    for le in value:
        if check_type(le):
            result.append(camel_to_pascal(le))
    return result

def convert_type(value,language):
    if value.count('[')>0 or value.count(']')>0 :
        value=value.replace('[', '')
        value=value.replace(']','')
        value = convert_type(value,language)
        if language == 'cs':
            return 'List<'+value+'>'
        if language == 'cpp':
            return 'std::list<'+value+'>'
    if not value in _TYPE_SUMARRY:
        value = camel_to_pascal(value)
    if language == 'cpp':
        if value == 'string':
            return 'std::'+value
        elif value == 'long':
            return 'int64_t'
        elif value == 'binary':
            return 'std::string'
    if language == 'cs':
        if value == 'binary':
            return 'byte[]'
    return value

def check_filepath(path):
    if not os.path.exists(path):
        sys.stderr.write (u"지정한 Path가 존재하지 않습니다:" + path)
        exit(1)
        return
    p = re.compile('/server/')
    if len(p.findall(path)) > 0:
        #Serverのpath
        return False
    else :
        #Clientのpath
        return True




def check_type(value):
    if value.count('[')>0 or value.count(']')>0 :
        value=value.replace('[','')
        value=value.replace(']','')
    for sumarry in _TYPE_SUMARRY:
        if sumarry == value :
            return False
    p = re.compile('\w')
    result = p.findall(value)
    if len(value) != len(result):
        print '데이터형 이름 입력 에러'
        sys.stderr.write(u'Type error ')
    return True

def replace_parentheses(value):
    if value.count('[')>0 or value.count(']')>0 :
        value=value.replace('[','')
        value=value.replace(']','')
    return value

def check_original_class(value):
    if value.count('[')>0 or value.count(']')>0 :
        value=value.replace('[','')
        value=value.replace(']','')
    for o_class in _originalclass:
        if o_class == value:
            return False
    return True

def check_existence_class(value):
    for name in _class_sumarry:
        if name == value.lower() :
            return True
    sys.stderr.write(u'클래스가 시트에 존재하지 않습니다 %s'%value)
    return False




# セルのデータを文字列として取得
def get_cell_string(sheet, row, column):
    value = get_cell_value(sheet, row, column)
    if value is None:
        return None
    # 文字列以外だったら文字列に変換
    if not isinstance(value, basestring):
        value = str(value)
    return value

def get_cell_value(sheet, row, column):
    cell = sheet.cell(row, column)
    if cell is None:
        return None
    value = cell.value

    # 데이터가 float일 때 int형으로 변환해도 문제 없는 경우는 int형으로 변형
    if isinstance(value, float) and value == int(value):
        value = int(value)

    return value


def setparam( param, item ):
    global _layout_maxreq_varname
    global _layout_maxreq_typelen
    global _layout_maxres_varname
    global _layout_maxres_typelen

    if param == 'include':
        _include.append(item)
    elif param == 'filename':
        _filename.append(item)
    elif param == 'classname':
        _classname.append(item)
    elif param == 'filepath':
        if check_filepath(item):
            _filepath_cs.append(item)

            # Param 파일 출력 디렉토리가 존재하지 않으면 생성한다
            output_dir_cs_param_ = _filepath_cs[0]+"/Param/"
            if not os.path.exists(output_dir_cs_param_):
                os.makedirs(output_dir_cs_param_)
        else :
            _filepath_cpp.append(item)

    elif param == 'member':
        if _signal_type == 'request':
            _request_member.append(item)
            _layout_maxreq_varname = max( len(item), _layout_maxreq_varname )
        elif _signal_type == 'response':
            _response_member.append(item)
            _layout_maxres_varname = max( len(item), _layout_maxres_varname )
        _member.append(item)

    elif param == 'originalclass':
        if _signal_type == 'request':
            _request_originalclass.append(convert_type(item,'cpp'))
        elif _signal_type == 'response':
            _response_originalclass.append(convert_type(item,'cpp'))
        _originalclass.append(convert_type(item,'cpp'))
    elif param == 'ifdef':
        _ifdef.append(item)
    elif param == 'define':
        _define.append(item)

    elif param == 'type':
        if _signal_type == 'request':
            _request_type.append(convert_type(item,'cs'))
            _request_type_cs.append(convert_type(item,'cs'))
            _request_type_cpp.append(convert_type(item,'cpp'))
            _layout_maxreq_typelen = max( len(convert_type(item,'cpp')), _layout_maxreq_typelen )
        elif _signal_type == 'response':
            _response_type.append(convert_type(item,'cs'))
            _response_type_cs.append(convert_type(item,'cpp'))
            _response_type_cpp.append(convert_type(item,'cpp'))
            _layout_maxres_typelen = max( len(convert_type(item,'cpp')), _layout_maxres_typelen )
        _type_cs.append(convert_type(item,'cs'))
        _type_cpp.append(convert_type(item,'cpp'))

    elif param == 'include_sub':
        _include_sub.append(item)
    elif param == 'class_sumarry':
        for summary in _class_sumarry:
            if summary == item.lower():
                sys.stderr.write( 'Class name Duplicated \n %s'%item )   #[Error] 클래스 이름 중복
                return
        _class_sumarry.append(item)
    elif param == 'comment':
        line = item.split('\n')
        if len(line) > 1:
            item = line[0]

        global _comment_type
        if _comment_type == 'member':
            if _signal_type == 'request':
                _comment_member_request.append(item)
            elif _signal_type == 'response':
                _comment_member_response.append(item)
            _comment_member.append(item)
        elif _comment_type == 'classname':
            _comment_class.append(item)

    else:
        print u'파라메터 에러'
        sys.stderr.write('param miss => %s\n'% param)


def clear_param():
    del _include[0:len(_include)]
    del _filename[0:len(_filename)]
    del _classname[0:len(_classname)]
    del _member[0:len(_member)]
    del _originalclass[0:len(_originalclass)]
    del _request_originalclass[0:len(_request_originalclass)]
    del _response_originalclass[0:len(_response_originalclass)]
    del _ifdef[0:len(_ifdef)]
    del _define[0:len(_define)]
    del _include_sub[0:len(_include_sub)]
    del _type_cpp[0:len(_type_cpp)]
    del _type_cs[0:len(_type_cs)]
    del _request_member[0:len(_request_member)]
    del _response_member[0:len(_response_member)]
    del _request_type[0:len(_request_type)]
    del _response_type[0:len(_response_type)]
    del _response_type_cpp[0:len(_response_type_cpp)]
    del _request_type_cpp[0:len(_request_type_cpp)]
    del _comment_member[0:len(_comment_member)]
    del _comment_class[0:len(_comment_class)]
    del _comment_member_response[0:len(_comment_member_response)]
    del _comment_member_request[0:len(_comment_member_request)]
    _layout_maxreq_typelen = 0
    _layout_maxreq_varname = 0
    _layout_maxres_typelen = 0
    _layout_maxres_varname = 0


def getparam(item):
    if item == 'include':
        return _include
    elif item == 'filename':
        return _filename
    elif item == 'classname':
        return _classname
    elif item == 'filepath':
        return _filepath
    elif item == 'member':
        return _member
    elif item == 'ifdef':
        return _ifdef
    elif item == 'define':
        return _define
    elif item == 'include_sub':
        return list(set(_include_sub))
    elif item == 'type_cpp':
        return _type_cpp
    elif item == 'type_cs':
        return _type_cs
    elif item == 'class_sumarry':
        return _class_sumarry
    elif item == 'filepath_cpp':
        return _filepath_cpp
    elif item == 'filepath_cs':
        return _filepath_cs
    elif item == 'request_member':
        return _request_member
    elif item == 'response_member':
        return _response_member
    elif item == 'request_type':
        return _request_type
    elif item == 'response_type':
        return _response_type
    elif item =='comment_member':
        return _comment_member
    elif item == 'comment_class':
        return _comment_class
    elif item == 'comment_member_request':
        return _comment_member_request
    elif item == 'comment_member_response':
        return _comment_member_response
    elif item == 'request_type_cpp':
        return _request_type_cpp
    elif item == 'response_type_cpp':
        return _response_type_cpp
    elif item == 'request_type_cs':
        return _request_type_cs
    elif item == 'response_type_cs':
        return _response_type_cs
    elif item == 'response_originalclass':
        #print list(set(_response_originalclass))
        return list(set(_response_originalclass))
    elif item == 'request_originalclass':
        return list(set(_request_originalclass))
    elif item == 'originalclass':
        #print _originalclass
        return list(set(_originalclass))
    elif item == 'layout_maxreq_typelen':
        return _layout_maxreq_typelen
    elif item == 'layout_maxreq_varname':
        return _layout_maxreq_varname
    elif item == 'layout_maxres_typelen':
        return _layout_maxres_typelen
    elif item == 'layout_maxres_varname':
        return _layout_maxres_varname


def sendparam(language):
    value={}
    if len( getparam('include') )!= 0:
        value['include']=getparam('include')
    if len( getparam('filename') )!= 0:
        value['filename']=getparam('filename')
    if len( getparam('classname') )!= 0:
        #C++のみクラス名をXxxxXxxxの形式に変換する
        if language == 'cpp':
            value['classname']=convert_classname(getparam('classname'))
        elif language == 'cs':
            value['classname']=getparam('classname')

    if len( getparam('member') )!= 0:
        value['member']=getparam('member')
    if  getparam('originalclass') != '':
        value['request_originalclass'] = getparam('request_originalclass')
        value['response_originalclass'] = getparam('response_originalclass')
        value['originalclass'] = getparam('originalclass')
    if len( getparam('ifdef') ) != 0 :
        value['ifdef'] = getparam('ifdef')
    if len( getparam('define') )!= 0:
        value['define'] = getparam('define')
    if len( getparam('include_sub') )!= 0:
        value['include_sub'] = getparam('include_sub')
    if len( getparam('request_member') )!= 0:
        value['request_member'] = getparam('request_member')
    if len( getparam('response_member') )!= 0:
        value['response_member'] = getparam('response_member')
    if len( getparam('response_type') )!= 0:
        value['response_type'] = getparam('response_type')
    if len( getparam('request_type') )!= 0:
        value['request_type'] = getparam('request_type')
    if len( getparam('comment_member_response') ) != 0:
        value['comment_member_response'] = getparam('comment_member_response')
    if len( getparam('comment_member_request') ) != 0:
        value['comment_member_request'] = getparam('comment_member_request')
    if len( getparam('request_type_cpp') ) != 0:
        value['request_type_cpp'] = getparam('request_type_cpp')
    if len( getparam('response_type_cpp') ) != 0:
        value['response_type_cpp'] = getparam('response_type_cpp')
    if len( getparam('request_type_cs') ) !=0:
        value['request_type_cs'] = getparam('request_type_cs')
    if len( getparam('response_type_cs') ) != 0:
        value['response_type_cs'] = getparam('response_type_cs')
    if getparam('layout_maxreq_typelen') != 0:
        value['layout_maxreq_typelen'] = getparam('layout_maxreq_typelen')
    if getparam('layout_maxreq_varname') != 0:
        value['layout_maxreq_varname'] = getparam('layout_maxreq_varname')
    if getparam('layout_maxres_typelen') != 0:
        value['layout_maxres_typelen'] = getparam('layout_maxres_typelen')
    if getparam('layout_maxres_varname') != 0:
        value['layout_maxres_varname'] = getparam('layout_maxres_varname')

    if language == 'cpp':
        value['type'] = getparam('type_cpp')
    if language == 'cs':
        value['type'] = getparam('type_cs')

    if language == 'cs' :
        value['filepath'] = getparam('filepath_cs')
    if language == 'cpp':
        value['filepath'] = getparam('filepath_cpp')

    value['comment_class'] = getparam('comment_class')
    value['comment_member'] = getparam('comment_member')
    return value


def SendParamForPacketID():
    global _packet_ids
    param = []

    for key, value in _packet_ids.iteritems():
        seq_no = 1
        for packet_name in value:
            packet_id = (int(key) << 16) + seq_no
            param.append( ( packet_name, packet_id ) )
            seq_no += 1

    return param


def set_signal_type(value):
    global _signal_type
    _signal_type= value

def set_comment_type(value):
    global _comment_type
    _comment_type = value


def createstring(st):

    return "_"+st.upper()+"_H_"

def camel_to_pascal(st):
    return st[:1].upper() + st[1:]






######################################
## CSV파일 로드 관련
######################################

# 파일 로드
def ConvData(path) :
    print u'프로토콜 자동 생성 중...'

    _filepath_cpp.append("./server/")
    _filepath_cs.append("./client/")

    fullPath = os.path.abspath(path)

    print "protocol_conv_Common.csv'"

    # common 파일 로드
    dataReaderCommon = OpenSCV(fullPath + "\protocol_conv_Common.csv")
    sheet = ReadCSVData(dataReaderCommon)
    ConvertProtocolCsv(sheet, "protocol_conv_Common.csv'")

    for dir in GetFiles(fullPath):

        if dir == 'protocol_conv_Common.csv' :
            continue;

        print dir

        dataReader = OpenSCV(fullPath + "/" + dir)
        sheet = ReadCSVData(dataReader)
        ConvertProtocolCsv(sheet, dir)

    FileWritePacketID()


# 디렉토리 리스트를 획득
def GetFiles(path):
    files = []
    for item in os.listdir(path):
        files.append(item)
    return files

def ReadCSVData(reader) :
    sheet = []

    row = 0
    col = 0

    for row in reader:

        col = []

        for val in row :
            col.append(val.decode('utf-8'))

        sheet.append(col)

    return sheet

# 파일 읽기
def OpenSCV(path) :
    if not os.path.exists(path):
        sys.stderr.write (u"file not found:" + path)
        quit()

    f = open(path, 'rb')

    data = csv.reader(f)

    return data


# 데이터에서 클래스를 작성한다
def ConvertProtocolCsv(sheet, file_name):
    SetClassName(sheet)
    category_no = PreparePacketID( sheet, file_name )

    column = 0
    for row in range(0, len(sheet)):
        cell_v1 = GetCellString(sheet, row, column)
        if cell_v1 == "common":
            SearchCellValue(sheet, row)
        if cell_v1 == '#':
            SearchCellValue(sheet, row)
            setparam('filename', file_name.lower())
            file_write_cs()
            file_write_cpp()
            AssignPacketID( category_no )


# 클래스 이름 리스트 사전을 작성
def SetClassName(sheet):
    #sheet = book.sheet_by_index(sheets)

    row_index = 0

    for row in sheet:
        value = GetCellString(sheet, row_index, 1)

        if value == '':
            row_index += 1
            continue

        if value == 'classname':
            class_name = GetCellString(sheet, row_index, 2)

            if class_name == '':
                sys.stderr.write('classname of null')
                return

            p = re.compile('\w')
            result = p.findall(class_name)

            if len(class_name) != len(result):
                sys.stderr.write(u'classnameType error ')
                return

            #print class_name
            setparam('class_sumarry', class_name.lower())

        row_index += 1

    #print u'\nクラス数\n'
    #print len(_class_sumarry)


# 패킷 ID설정을 준비한다.
# - csv파일에 카테고리넘버 값을 명시하지 않으면, Default값은 0이다.
def PreparePacketID( sheet, file_name ):
    global _packet_ids
    category_no = 0

    first_cell = GetCellString( sheet, 0, 0 )
    if first_cell == '@category':
        category_no = int( GetCellValue(sheet, 0, 1) )

    if category_no in _packet_ids:
        sys.stderr.write( '[ERROR] 중복된 카테고리 넘버: ' + str(category_no) + ', File: ' + file_name )
        quit()

    _packet_ids[ category_no ] = []
    return category_no


def AssignPacketID( category_no ):
    global _packet_ids
    _packet_ids[ category_no ].append( copy.deepcopy( _classname[0] ) )


#$$ TEST
def TestCode():
    global _packet_ids

    pktData1 = (1, 'pktMove')
    pktData2 = (2, 'pktAttack')
    pktData3 = (3, 'pktSleep')

    action_array = []
    action_array.append( pktData1 )
    action_array.append( pktData2 )
    action_array.append (pktData3 )

    _packet_ids[ 0 ] = action_array



# 셀 데이터를 문자열로 취득
def GetCellString(sheet, row, column):
    value = GetCellValue(sheet, row, column)

    if value is '<>':
        return '<>'

    # 문자열인지 타입 검사. 문자열이 아니면 문자열로 변경
    if not isinstance(value, basestring):
        value = str(value)

    return value


# 셀의 값을 취득
def GetCellValue(sheet, row, column):
    cell = sheet[row][column]

    if cell is '<>':
        return '<>'

    # データがfloat型かつint型に変換しても問題ない場合はint型に変換
    if isinstance(cell, float) and cell == int(cell):
        cell = int(cell)

    return cell


# 셀에 저장되어 있는 데이터를 추출
def SearchCellValue(sheet, startrow):
    # 파라미터 클리어
    clear_param()

    columns = 1
    row_index = 0

    for rows in range(startrow, len(sheet) ):

        cell_value1 = GetCellString(sheet, rows, columns)

        if GetCellString(sheet, rows, 0) != '':
                    set_signal_type(GetCellString(sheet, rows, 0))

        if check_param(cell_value1):
            if cell_value1 != "":
                cell_value2 = GetCellString(sheet, rows, columns + 1)

                if cell_value2 == "":
                    sys.stderr.write( 'Forget input in cell <C>\n' )
                    continue

                # <B>셀이 member 일 경우
                if cell_value1 == 'member':

                    if check_type(cell_value2):

                        if check_existence_class(replace_parentheses(cell_value2)):
                            if check_original_class(cell_value2):

                            # 공통 클래스 중에 파일포함 및 변수 선언을 추가
                                setparam('originalclass', replace_parentheses(cell_value2))

                            # INCLUDE
                                setparam('include_sub', replace_parentheses(cell_value2).lower() + '.h')
                        else :
                            continue

                    set_comment_type(cell_value1)
                    setparam("comment", GetCellString(sheet, rows, columns + 4) )

                    if GetCellString(sheet, rows, columns + 2) != "":
                        setparam('member', GetCellString(sheet, rows, columns + 2))

                    else:
                        sys.stderr.write('input cell D')

                    setparam('type',cell_value2)

                # <B>셀이 classname 일 경우
                elif cell_value1 == 'classname':
                    set_comment_type(cell_value1)
                    global _comment_type
                    setparam("comment", GetCellString(sheet, rows, columns + 4) )
                    setparam('classname', cell_value2)

                    # ifdef,define의 문자열 생성  [$$필요없으니 지우자]
                    setparam('ifdef', createstring(cell_value2))
                    setparam('define', createstring(cell_value2))

                elif cell_value1 == 'filepath':
                    setparam('filepath', cell_value2)


            if cell_value1 == "" and GetCellString(sheet, rows-1, columns) != "" :
                return
        else:
            return


######################################

if __name__ == '__main__':
    start = time.time()
    argvs = sys.argv
    argc = len(argvs)

    if (argc != 2):   # 引数が足りない場合は、その旨を表示

        print u'인수가 부족합니다'
        sys.stderr.write(u'인수가 부족합니다\n')
        quit()

    path = argvs[1]
    if not os.path.isdir(path):
        print '디렉토리 Path를 지정해 주세요'
        sys.stderr.write (u"지정한 파일이 존재하지 않습니다:" + path)

    ConvData(path)
    elapsed_time = time.time() - start
    #print("elapsed_time:{0}".format(elapsed_time))