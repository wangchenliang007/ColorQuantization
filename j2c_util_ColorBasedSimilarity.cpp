#include "j2c_util_ColorBasedSimilarity.h"
#include <string.h>

JNIEXPORT jobject JNICALL Java_j2c_util_ColorBasedSimilarity_getCBSList
  (JNIEnv * env , jobject , jobject image_list){
      jclass cls_image_list = env->GetObjectClass(image_list);//image_list的类
      jmethodID image_list_get = env->GetMethodID(cls_image_list,"get","(I)java/lang/Object");
      jmethodID image_list_size = env->GetMethodID(cls_image_list,"size","()I");
      jint len = env->CallIntMethod(cls_image_list,"size","()I");
      printf("get java List object by C++ , then print it...../n");
       for(int i=0;i<len;i++){
                jobject obj_image = env->CallObjectMethod(image_list,image_list_get,i);
                jclass cls_image = env->GetObjectClass(obj_image); //

                jmethodID image_getFilename = env->GetMethodID(cls_image,"getFilename","()Ljava/lang/String;");
                jmethodID image_getSimilarity = env->GetMethodID(cls_image,"getSimilarity","()D");


                jstring filename = (jstring)env->CallObjectMethod(obj_image,image_getFilename);
                jlong similar = env->CallLongMethod(obj_image,image_getSimilarity);//相似度

        }

        return image_list;
  }
