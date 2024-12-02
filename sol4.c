#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define DIR_MAX 100  // 최대 디렉토리 개수
#define FILE_MAX 1024 // 파일 경로 최대 길이

// 디렉토리 및 하위 디렉토리를 재귀적으로 탐색하는 함수
void listDir(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;

    // 디렉토리 열기
    if (!(dir = opendir(path))) {
        perror("opendir failed");
        return;
    }

    // 현재 디렉토리 경로 출력
    printf("\n%s:\n", path);

    // 디렉토리 내 항목 탐색
    while ((entry = readdir(dir)) != NULL) {
        char fullPath[FILE_MAX];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        // 파일 상태 확인
        if (stat(fullPath, &st) == -1) {
            perror("stat failed");
            continue;
        }

        // 디렉토리인 경우
        if (S_ISDIR(st.st_mode)) {
            // "."와 ".."은 건너뛰기
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            printf("[DIR]  %s\n", entry->d_name);
        } else {
            // 일반 파일인 경우
            printf("       %s\n", entry->d_name);
        }
    }

    // 하위 디렉토리 탐색
    rewinddir(dir);  // 디렉토리 읽기 위치 초기화
    while ((entry = readdir(dir)) != NULL) {
        char fullPath[FILE_MAX];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        // 파일 상태 확인
        if (stat(fullPath, &st) == -1)
            continue;

        // 하위 디렉토리가 있으면 재귀 호출
        if (S_ISDIR(st.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            listDir(fullPath);  // 재귀 호출
        }
    }

    closedir(dir); // 디렉토리 닫기
}

int main(int argc, char *argv[]) {
    char dir[FILE_MAX];

    // 인자가 없으면 현재 디렉토리, 있으면 해당 경로
    if (argc == 1)
        strcpy(dir, ".");
    else
        strncpy(dir, argv[1], sizeof(dir) - 1);  // 인자 길이 안전하게 복사

    // 디렉토리 탐색 시작
    listDir(dir);

    return 0;
}

