// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Play->OnClicked.AddDynamic(this, &UMenuWidget::OnClickPlay);
	btn_Pause->OnClicked.AddDynamic(this, &UMenuWidget::OnClickPause);
	btn_Key->OnClicked.AddDynamic(this, &UMenuWidget::OnClickKey);
	btn_GoRobby->OnClicked.AddDynamic(this, &UMenuWidget::OnClickGoRobby);
	btn_Quit->OnClicked.AddDynamic(this, &UMenuWidget::OnClickQuit);


}

void UMenuWidget::OnClickPlay()
{
	// 일시정지된 게임을 다시 Play상태로 돌림
}

void UMenuWidget::OnClickPause()
{
	// Game을 일시정지함
}

void UMenuWidget::OnClickKey()
{
	// 조작 Key Image를 눈 앞에 보여줌
}

void UMenuWidget::OnClickGoRobby()
{
	// 맵 RobbyMaps로 이동
	UGameplayStatics::OpenLevel(GetWorld(), "RobbyMaps");
}

void UMenuWidget::OnClickQuit()
{
	// 현재 실행중인 월드 오브젝트를 가져오기
	UWorld* currentWorld = GetWorld();

	// 앱 종료
	UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
