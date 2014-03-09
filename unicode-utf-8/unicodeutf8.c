#include <stdio.h>
#include<string.h>
#include<malloc.h>
#include<wchar.h>
#include<assert.h>

wchar_t * ConvertUtf8ToUnicode(char * putf8)
{
  int i,k,len;
  printf("%s",putf8);
  assert(putf8);
  len=strlen(putf8);
  wchar_t * result=(wchar_t*)malloc(sizeof(wchar_t)*len);
  if(result){
    k=0;
	for(i=0;i<len;){
	  if(0==(0x80&putf8[i])){
	    result[k++]=(wchar_t)putf8[i++];
		continue;
	  }
	  if(0xe0==(0xe0&putf8[i]))
	  {
	    result[k]=(putf8[i]&0x1F)<<12;
		result[k] |=(putf8[i+1]&0x3F) <<6;
		result[k++]|=(putf8[i+2]&0x3F);
		i+=3;
		continue;
	  }
	  if(0xc0==0xc0&putf8[i]){
	    result[k]=(putf8[i]&0x1F)<<8;
		result[k++] |=(putf8[i+1]&0x3F);
		i+=2;
	  }
	}
   result[k++]=0;
  }
  return result;
}


char * ConvertUnicodeToUtf8(wchar_t *punicode)
{
  int i,k,len;
  assert(punicode);
  len=wcslen(punicode);
  char *result=(char *)malloc(sizeof(char)*len*3);
  if(NULL!=result)
  {
    k=0;
	for(i=0;i<len;i++)
	{
	  if(0x80>punicode[i])
	  {
	    result[k++]=(char)punicode[i];
	  }else{
	    result[k++]=(char)(0xe0|(punicode[i]>>12));
		result[k++]=(char)(0x80|((punicode[i]>>6)&0x3f));
		result[k++]=(char)(0x80|(punicode[i]&0x3f));
	  }
	}
  result[k++]=0;
  }
  return result;
}

int main()
{
  char * ss="1235";
  char *r=ConvertUtf8ToUnicode(ss);
  printf("%s",r);
  return 0;
}