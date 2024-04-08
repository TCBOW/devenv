#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
class ThreadTest {
    private:
        pthread_t thread_handler;
        pthread_mutex_t mutex;
        int data;
    public:
        ThreadTest(){
            data = 0;
        }

        // data に値を代入
        // executeが優先権を保持している間は待機する
        //
        void setData(int i){
            std::cout << "wait mutex" << std::endl;
            pthread_mutex_lock(&(this->mutex)); // 優先権を獲得するまで待機
            data = i;
            pthread_mutex_unlock(&(this->mutex)); // 優先権を破棄
            std::cout << "set Data finished!" << std::endl;
        }
        int getData(){ return data; }

        // ランチャ
        //
        static void* executeLauncher(void* args){
            std::cout << "executeLauncher" << std::endl;
            // 引数にわたされたインスタンスを無理やりキャストしてインスタンスメソッドを実行
            reinterpret_cast<ThreadTest*>(args)->execute();
            return (void*)nullptr;
        }

        // スレッド開始
        void threadStart(){
            if (this->thread_handler == 0){
                std::cout << "threadStart" << std::endl;
                pthread_mutex_init(&(this->mutex), nullptr); // ミューテックスの初期化
                pthread_create(
                        &(this->thread_handler),
                        nullptr,
                        &ThreadTest::executeLauncher,
                        this
                        );
            }
        }

        // スレッドで実行したいインスタンスメソッド
        //
        void execute(){
            while(1){
                pthread_testcancel();
                pthread_mutex_lock(&(this->mutex));
                std::cout << "execute" << std::endl;
                std::cout << "Data = " << (this->getData()) << std::endl;
                sleep(10);
                pthread_mutex_unlock(&(this->mutex)); // 優先権を破棄
                sleep(1);
            }
        }

        // デストラクタ
        // * 終了時にスレッドにキャンセル要求を投げる
        //
        ~ThreadTest(){
            std::cout << "destructor start" << std::endl;
            pthread_cancel(this->thread_handler);
            pthread_join(this->thread_handler, nullptr);
            std::cout << "destructor end" << std::endl;
        }
};

int main()
{
    ThreadTest* matrix = new ThreadTest();
    ThreadTest* matrix2 = new ThreadTest();
    matrix->setData(10);
    matrix->threadStart();
    matrix2->setData(150);
    matrix2->threadStart();
    sleep(1);
    matrix2->setData(300);
    matrix->setData(20);
    sleep(30);
    delete matrix;
    delete matrix2;
}
