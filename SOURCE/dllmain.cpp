#define RVA(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))
#define M_PI	3.14159265358979323846264338327950288419716939937510
#define _CRT_SECURE_NO_WARNINGS
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_D3D11_IMPLEMENTATION
#define NK_IMPLEMENTATION

#include "Nuklear/nuklear.h"
#include "Nuklear/demo/d3d11/nuklear_d3d11.h"
#include "MemoryHelper.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <D3D11.h>
#include <codecvt>
#include <Psapi.h>
#include <list>
#include <tchar.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include <regex>
#include <winuser.h>
#include <WinReg.h>
#include <winternl.h>
#include <TlHelp32.h>
#include "lazy.h"
#include "xor.h"
#include "SDK.hpp"
#include "MinHook.h"

typedef int (WINAPI* LPFN_MBA)(DWORD);
static LPFN_MBA NtGetAsyncKeyState;

bool ShowMenu = true;
static ID3D11DeviceContext* m_pContext;
static ID3D11RenderTargetView* g_pRenderTargetView;
static IDXGISwapChain* g_pSwapChain;
static WNDPROC oWndProc;
static ID3D11Device* uDevice;

HRESULT(*present_original)(IDXGISwapChain* swapchain, UINT sync, UINT flags) = nullptr;
#define ReadBYTE(base, offset) (*(((PBYTE)base + offset)))
nk_context* g_pNkContext;

enum theme { THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK, THEME_PURPLE };
static void




set_style(struct nk_context* ctx, enum theme theme)
{
	struct nk_color table[NK_COLOR_COUNT];
	if (theme == THEME_WHITE) {
		table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
		table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
		table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_RED) {
		table[NK_COLOR_TEXT] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(255, 255, 255, 255);
		table[NK_COLOR_HEADER] = nk_rgba(255, 255, 255, 255);
		table[NK_COLOR_BORDER] = nk_rgba(255, 255, 255, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(0, 255, 0, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SELECT] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(0, 255, 0, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(0, 255, 0, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(4, 4, 4, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_BLUE) {
		table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
		table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
		table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_DARK) {
		table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
		table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
		table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_PURPLE)
	{
		table[NK_COLOR_TEXT] = nk_rgba(245, 15, 15, 0.9);
		table[NK_COLOR_WINDOW] = nk_rgba(14, 0, 14, 0.9);
	}
	else {
		nk_style_default(ctx);
	}
}

typedef HRESULT(*present_fn)(IDXGISwapChain*, UINT, UINT);
inline present_fn original_present{ };

AFortPlayerPawn* EnemyPlayer;
AFortPlayerPawn* LocalPawn;

inline UKismetMathLibrary* MathLib = NULL;
inline UGameplayStatics* GameplayStatics = NULL;
inline UFortKismetLibrary* FortKismetLib = NULL;
inline UKismetSystemLibrary* KismetSystemLibrary = NULL;
inline APlayerController* PlayerController;
inline int bShowFOV = 0;
inline int bVisibleCheck = 0;

inline int Aimbot = 0;
inline int box = 0;
inline int silent = 0;
inline int line = 0;
inline int boathax = 0;
inline int noclip = 0;
inline int FOV = 20;
inline int speedf = 0;
inline int rapid = 0;
static int Smooth = 1.0f;

FRotator inline RotatorAdd(FRotator Vector1, FRotator Vector2)
{
	FRotator Vec;
	Vec.Pitch = Vector1.Pitch + Vector2.Pitch;
	Vec.Yaw = Vector1.Yaw + Vector2.Yaw;
	Vec.Roll = Vector1.Roll + Vector2.Roll;
	return Vec;
}

FRotator inline SmoothOutRotation(FRotator rStartRotation, FRotator rEndRotation, float X, float Y)
{
	int ScreenCenterX = X / 2.0f;
	int ScreenCenterY = Y / 2.0f;

	FRotator rDeltaRotation;

	rDeltaRotation = MathLib->STATIC_NormalizedDeltaRotator(rEndRotation, rStartRotation);
	float TargetX = rDeltaRotation.Yaw - ScreenCenterX;
	float TargetY = rDeltaRotation.Pitch - ScreenCenterX;

	TargetX /= Smooth;
	TargetY /= Smooth;

	// yaw
	if (rDeltaRotation.Yaw /= Smooth) { rDeltaRotation.Yaw /= Smooth; }
	else if (rDeltaRotation.Yaw /= -Smooth) { rDeltaRotation.Yaw /= -Smooth; }

	// pitch
	if (rDeltaRotation.Pitch /= Smooth) { rDeltaRotation.Pitch /= Smooth; }
	else if (rDeltaRotation.Pitch /= -Smooth) { rDeltaRotation.Pitch /= -Smooth; }

	return RotatorAdd(rStartRotation, rDeltaRotation);
}

uintptr_t ResolveRelativeAddress(uintptr_t Address, int InstructionLength)
{
	DWORD Offset = *(DWORD*)(Address + (InstructionLength - 4));
	return Address + InstructionLength + Offset;
}

static FMatrix* myMatrix = new FMatrix();
bool GetBoneMatrix(ACharacter* pActor, int id, FVector* out)
{
	static uintptr_t pGetBoneMatrix = 0;
	if (!pGetBoneMatrix)
		pGetBoneMatrix = PatternScan(_("48 8B C4 48 89 58 10 44 89 40 18 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC ? ? ? ? 0F 29 78 B8"), 0);

	auto fGetBoneMatrix = ((FMatrix * (__fastcall*)(USkeletalMeshComponent*, FMatrix*, int))(pGetBoneMatrix));
	fGetBoneMatrix(pActor->Mesh, myMatrix, id);

	out->X = myMatrix->M[3][0];
	out->Y = myMatrix->M[3][1];
	out->Z = myMatrix->M[3][2];

	return true;
}

bool GetBoneScreen(ACharacter* pActor, int nBone, FVector2D* vBonePos)
{
	if (!pActor) return false;

	FVector vWorldPos;
	if (!GetBoneMatrix(pActor, nBone, &vWorldPos))
		return false;

	if (!PlayerController->ProjectWorldLocationToScreen(vWorldPos, false, vBonePos))
		return false;

	return true;
}

bool IsAiming()
{
	return NtGetAsyncKeyState(VK_RBUTTON);
}

FVector2D inline Subtract(FVector2D point1, FVector point2)
{
	FVector2D vector{ 0, 0 };
	vector.X = point1.X - point2.X;
	vector.Y = point1.Y - point2.Y;
	return vector;
}

inline float GetDistance2D(FVector2D point1, const FVector& point2)
{
	FVector2D heading = Subtract(point1, point2);
	float distanceSquared;
	float distance;

	distanceSquared = heading.X * heading.X + heading.Y * heading.Y;
	distance = MathLib->STATIC_Sqrt(distanceSquared);

	return distance;
}


BOOL(*LOSFNTEMPLATE)(PVOID PlayerController, PVOID Actor, FVector* ViewPoint) = nullptr;
BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, FVector* ViewPoint) {
	return LOSFNTEMPLATE(PlayerController, Actor, ViewPoint);
}


uintptr_t cUWorld = 0;

bool EntitiyLoop()
{

	if (bShowFOV) Renderer->DrawFOV(FOV);


	static bool isPawnValid = false;
	float closest_distance = FLT_MAX;

	if (!GameplayStatics) GameplayStatics = (UGameplayStatics*)UGameplayStatics::StaticClass();
	if (!FortKismetLib) FortKismetLib = (UFortKismetLibrary*)UFortKismetLibrary::StaticClass();
	if (!KismetSystemLibrary) KismetSystemLibrary = (UKismetSystemLibrary*)UKismetSystemLibrary::StaticClass();
	if (!MathLib) MathLib = (UKismetMathLibrary*)UKismetMathLibrary::StaticClass();

	UWorld* GWorld = (UWorld*)*(uintptr_t*)cUWorld;
	if (!GWorld) return false;

	auto OwningGameInstance = GWorld->OwningGameInstance;
	if (!OwningGameInstance) return false;

	PlayerController = OwningGameInstance->LocalPlayers[0]->PlayerController;
	if (!PlayerController) return false;

	LocalPawn = (AFortPlayerPawnAthena*)PlayerController->AcknowledgedPawn;
	if (!LocalPawn) isPawnValid = false; else isPawnValid = true;

	auto CameraController = PlayerController->PlayerCameraManager;
	if (!CameraController) return false;

	auto CameraLocation = CameraController->GetCameraLocation();
	auto CameraRotation = CameraController->GetCameraRotation();
	auto FOVAngle = CameraController->GetFOVAngle();

	auto AllPlayerPawns = FortKismetLib->STATIC_GetFortPlayerPawns(GWorld);
	if (isPawnValid)
	{
		if (boathax)
		{
			TArray<AActor*> Boats;
			GameplayStatics->STATIC_GetAllActorsOfClass(GWorld, (AActor*)AFortMeatballVehicle::StaticClass(), &Boats);

			for (int i = 0; i < Boats.Num(); i++)
			{
				AFortMeatballVehicle* BoatActors = (AFortMeatballVehicle*)Boats[i];
				if (!BoatActors) continue;

				FVector LootLoc = BoatActors->K2_GetActorLocation();
				FVector2D LootLoc2D;

				if (LocalPawn->IsInVehicle())
				{
					if (boathax)
					{
						BoatActors->FortMeatballVehicleConfigs->BoostMinPushForce = (1200.0f * speedf);
						BoatActors->FortMeatballVehicleConfigs->BoostTopSpeedForceMultiplier = (1.3f * speedf);
						BoatActors->FortMeatballVehicleConfigs->BoostTopSpeedMultiplier = (1.3f * speedf);
						BoatActors->FortMeatballVehicleConfigs->LandTopSpeedMultiplier = (1.0f * speedf);
						BoatActors->FortMeatballVehicleConfigs->LandPushForceMultiplier = (3.0f * speedf);
						BoatActors->FortMeatballVehicleConfigs->BoostSteeringMultiplier = 1.0f;
						BoatActors->FortMeatballVehicleConfigs->LandSteeringMultiplier = 1.0f;
						BoatActors->FortMeatballVehicleConfigs->LandMinSpeedSteeringAngle = 180.0f;
						BoatActors->FortMeatballVehicleConfigs->LandMaxSpeedSteeringAngle = 180.0f;
					}
					else
					{
						BoatActors->FortMeatballVehicleConfigs->BoostMinPushForce = 1200;
						BoatActors->FortMeatballVehicleConfigs->BoostTopSpeedForceMultiplier = 1.29;
						BoatActors->FortMeatballVehicleConfigs->BoostTopSpeedMultiplier = 1.29;
						BoatActors->FortMeatballVehicleConfigs->LandTopSpeedMultiplier = 0.1;
						BoatActors->FortMeatballVehicleConfigs->LandPushForceMultiplier = 3;
						BoatActors->FortMeatballVehicleConfigs->BoostSteeringMultiplier = 0.2;
						BoatActors->FortMeatballVehicleConfigs->LandSteeringMultiplier = 1;
						BoatActors->FortMeatballVehicleConfigs->LandMinSpeedSteeringAngle = 180;
						BoatActors->FortMeatballVehicleConfigs->LandMaxSpeedSteeringAngle = 25;
					}
				}
			}
		}

		for (int i = 0; i < AllPlayerPawns.Num(); i++)
		{
			AFortPlayerPawn* Actor = AllPlayerPawns[i];

			if (FortKismetLib->STATIC_OnSameTeam(LocalPawn, Actor)) continue; //dont need local check cuz team check alr 
			if (Actor->IsDead()) continue;

			FVector2D target;
			GetBoneScreen(Actor, 66, &target);

			if (!target.X && !target.Y) continue;

			auto dist = GetDistance2D(FVector2D(X, Y) / 2, FVector(target.X, target.Y, 0));

			bool isVisible = false;

			nk_color col = { 255,255,255,255 }; // 0,255,0,255

			FVector viewPoint = FVector{ 0, 0, 0 };


			if (LineOfSightTo((PVOID)PlayerController, (PVOID)Actor, &viewPoint))
			{
				col = { 255,0,0,255 }; // 0,255,0,255
				isVisible = true;
			}

			FVector2D bottom;
			GetBoneScreen(Actor, 0, &bottom);

			if (dist < FOV && dist < closest_distance)
			{
				EnemyPlayer = Actor;
				if (Aimbot && isVisible)
				{
					FVector AimLocation;
					GetBoneMatrix(Actor, 66, &AimLocation);

					FRotator AimAtRotation = MathLib->STATIC_FindLookAtRotation(CameraLocation, AimLocation);

					AimAtRotation = SmoothOutRotation(CameraRotation, AimAtRotation, X, Y);

					if (NtGetAsyncKeyState(VK_RBUTTON))
						PlayerController->ClientSetRotation(AimAtRotation, false);
				}

				closest_distance = dist;
			}

			FVector headout;
			GetBoneMatrix(Actor, 66, &headout);
			FVector2D HeadBox;
			PlayerController->ProjectWorldLocationToScreen(headout, false, &HeadBox);

			float H = HeadBox.Y - bottom.Y;
			if (H < 0) H = H * (-1.f);
			float W = H * 0.65;

			if (box)
			{
				float CornerHeight = abs(HeadBox.Y - bottom.Y);
				float CornerWidth = CornerHeight * 0.55;
				Renderer->DrawCorneredBox(HeadBox.X - (CornerWidth / 2), HeadBox.Y, CornerWidth, CornerHeight, col, 1.5);
			}

			if (line)
			{
				Renderer->DrawLine(X / 2, Y, bottom.X, bottom.Y, 1, col);
			}

			if (noclip)
			{

			}

			if (rapid)
			{
				auto LocalWeapon = LocalPawn->CurrentWeapon;
				auto bLastFireTime = LocalWeapon->LastFireTime;
				auto bLastFireTimeVerified = LocalWeapon->LastFireTimeVerified;
				LocalWeapon->LastFireTime = bLastFireTime + bLastFireTimeVerified - 4;
			}
		}
	}
	return true;
}

HRESULT present_hooked(IDXGISwapChain* swapchain, UINT sync, UINT flags)
{
	ID3D11Texture2D* pRenderTargetTexture;

	g_pSwapChain = swapchain;

	if (firstTime) {

		g_pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&uDevice);

		if (!uDevice) return false;

		uDevice->GetImmediateContext(&m_pContext);

		if (!m_pContext) return false;

		g_pNkContext = nk_d3d11_init((ID3D11Device*)uDevice, (int)X, (int)Y, (unsigned int)MAX_VERTEX_BUFFER, (unsigned int)MAX_INDEX_BUFFER);
		{
			nk_d3d11_font_stash_begin(&Renderer->atlas);
			nk_d3d11_font_stash_end();

			Renderer->CopyContext = g_pNkContext;
		}

		if (SUCCEEDED(g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
		{
			uDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
			pRenderTargetTexture->Release();
			uDevice->Release();
		}

		firstTime = false;
	}

	if (!g_pRenderTargetView)
	{
		g_pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&uDevice);

		if (!uDevice) return false;

		uDevice->GetImmediateContext(&m_pContext);

		if (!m_pContext) return false;

		if (SUCCEEDED(g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pRenderTargetTexture)))
		{
			uDevice->CreateRenderTargetView(pRenderTargetTexture, NULL, &g_pRenderTargetView);
			pRenderTargetTexture->Release();
			uDevice->Release();
		}
	}

	if (g_pRenderTargetView)
	{
		m_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);

		nk_input_end(g_pNkContext);

		nk_end(g_pNkContext);

		if (NtGetAsyncKeyState(VK_INSERT) == -32767)
			ShowMenu = !ShowMenu;

		if (ShowMenu)
		{



			set_style(g_pNkContext, THEME_RED);
			if (nk_begin(g_pNkContext, _("ElloCheats.cc"), nk_rect(50, 50, 400, 400), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE
				| NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_SCALABLE))
			{
				nk_layout_row_static(g_pNkContext, 30, 100, 30);
				
					
				nk_checkbox_label(g_pNkContext, _("Memory"), &Aimbot);
				nk_checkbox_label(g_pNkContext, _("Silent"), &silent);
				nk_layout_row_static(g_pNkContext, 30, 100, 30);
				
					
				nk_checkbox_label(g_pNkContext, _("Draw box"), &box);
				nk_checkbox_label(g_pNkContext, _("Draw line"), &line);
				nk_layout_row_static(g_pNkContext, 30, 100, 30);
			
				
				nk_checkbox_label(g_pNkContext, _("Show FOV"), &bShowFOV);
				nk_layout_row_dynamic(g_pNkContext, 30, 2);
				nk_label(g_pNkContext, _("FOV Circle"), NK_TEXT_LEFT);
				nk_slider_int(g_pNkContext, 1, &FOV, 1000, 1);
				nk_layout_row_dynamic(g_pNkContext, 30, 2);
				nk_layout_row_dynamic(g_pNkContext, 30, 2);
				nk_label(g_pNkContext, _("Smoothing"), NK_TEXT_LEFT);
				nk_slider_int(g_pNkContext, 1, &Smooth, 5, 1);
			}
			nk_end(g_pNkContext);
		}

		else
		{
			if (nk_begin(g_pNkContext, " ", nk_rect(1, 1, 1, 1), NK_WINDOW_MINIMIZED))
			{
			}

			nk_end(g_pNkContext);
		}

		nk_input_begin(g_pNkContext);

		nk_d3d11_render(m_pContext, NK_ANTI_ALIASING_ON);
	
		nk_end(g_pNkContext);
	}

	return original_present(swapchain, sync, flags);
}

LRESULT CALLBACK hkWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_SIZE:
		UINT width = LOWORD(lparam);
		UINT height = HIWORD(lparam);

		ID3D11Texture2D* back_buffer;
		D3D11_RENDER_TARGET_VIEW_DESC desc;
		HRESULT hr;

		if (g_pRenderTargetView)
		{
			g_pRenderTargetView->Release();
			g_pRenderTargetView = nullptr;
		}

		if (m_pContext)
		{
			m_pContext->OMSetRenderTargets(0, NULL, NULL);
			if (g_pSwapChain) g_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

			nk_d3d11_resize(m_pContext, (int)width, (int)height);
		}
		break;
	}

	nk_d3d11_handle_event(hwnd, msg, wparam, lparam);

	return CallWindowProcW(oWndProc, hwnd, msg, wparam, lparam);
}
float* (*SILENTSHOTCALCULATOR)(PVOID, PVOID, PVOID) = nullptr;
float* SILENTSHOTCALCULATORHook(PVOID arg0, PVOID arg1, PVOID arg2) {
	auto ret = SILENTSHOTCALCULATOR(arg0, arg1, arg2);
	if (ret && silent && LocalPawn && EnemyPlayer) {

		auto root = LocalPawn->RootComponent->RelativeLocation;
		FVector head;
		GetBoneMatrix(EnemyPlayer, 66, &head);

		auto dx = head.X - root.X;
		auto dy = head.Y - root.Y;
		auto dz = head.Z - root.Z;
		if (dx * dx + dy * dy + dz * dz < 125000.0f) {
			ret[4] = head.X;
			ret[5] = head.Y;
			ret[6] = head.Z;
		}
		else {
			head.Z -= 16.0f;
			root.Z += 45.0f;

			auto y = atan2f(head.Y - root.Y, head.X - root.X);

			root.X += cosf(y + 1.5708f) * 32.0f;
			root.Y += sinf(y + 1.5708f) * 32.0f;

			auto length = sqrtf(powf(head.X - root.X, 2) + powf(head.Y - root.Y, 2));
			auto x = -atan2f(head.Z - root.Z, length);
			y = atan2f(head.Y - root.Y, head.X - root.X);

			x /= 2.0f;
			y /= 2.0f;

			ret[0] = -(sinf(x) * sinf(y));
			ret[1] = sinf(x) * cosf(y);
			ret[2] = cosf(x) * sinf(y);
			ret[3] = cosf(x) * cosf(y);
		}
	}

	return ret;
}

bool InitializeHack()
{
	//LI_FN(AllocConsole)();
	//FILE* fp;
	//freopen_s(&fp, _("CONOUT$"), _("w"), stdout);

	X = LI_FN(GetSystemMetrics)(SM_CXSCREEN);
	Y = LI_FN(GetSystemMetrics)(SM_CYSCREEN);
	MH_Initialize();

	auto addr = PatternScan(_("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F1"));
	MH_CreateHook((LPVOID)addr, (LPVOID)SILENTSHOTCALCULATORHook, (LPVOID*)&SILENTSHOTCALCULATOR);
	MH_EnableHook((LPVOID)addr);
	NtGetAsyncKeyState = (LPFN_MBA)LI_FN(GetProcAddress)(LI_FN(GetModuleHandleA)(_("win32u.dll")), _("NtUserGetAsyncKeyState"));

	auto level = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC sd;
	{
		ZeroMemory(&sd, sizeof sd);
		sd.BufferCount = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = LI_FN(FindWindowA)(_("UnrealWindow"), nullptr);
		sd.SampleDesc.Count = 1;
		sd.Windowed = TRUE;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	IDXGISwapChain* swap_chain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	LI_FN(D3D11CreateDeviceAndSwapChain)(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &level, 1, D3D11_SDK_VERSION, &sd, &swap_chain, &device, nullptr, &context);

	auto* swap_chainvtable = reinterpret_cast<uintptr_t*>(swap_chain);
	swap_chainvtable = reinterpret_cast<uintptr_t*>(swap_chainvtable[0]);

	DWORD old_protect;
	original_present = reinterpret_cast<present_fn>(reinterpret_cast<DWORD_PTR*>(swap_chainvtable[8]));
	LI_FN(VirtualProtect)(swap_chainvtable, 0x1000, PAGE_EXECUTE_READWRITE, &old_protect);
	swap_chainvtable[8] = reinterpret_cast<DWORD_PTR>(present_hooked);
	LI_FN(VirtualProtect)(swap_chainvtable, 0x1000, old_protect, &old_protect);

	HWND test = FindWindowA(_("UnrealWindow"), _("Fortnite  "));

	cUWorld = PatternScan(_("48 8B 05 ? ? ? ? 4D 8B C2"));
	cUWorld = ResolveRelativeAddress(cUWorld, 7);

	// FUCK SDKS
	auto RES = PatternScan(_("48 8B C4 55 53 56 57 41 54 41 55 41 56 48 8D 68 A8"));
	LOSFNTEMPLATE = reinterpret_cast<decltype(LOSFNTEMPLATE)>(RES);

	std::cout << "0x" << std::hex << cUWorld << std::endl;

	oWndProc = (WNDPROC)SetWindowLongPtrW(test, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InitializeHack();
	}
	return TRUE;
}