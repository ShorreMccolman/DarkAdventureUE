// Fill out your copyright notice in the Description page of Project Settings.

#include "DAEquipmentWidget.h"


void UDAEquipmentWidget::NavigateUp()
{
	UDAWidget::NavigateUp();
	UpdateItemInfoPanel();
}

void UDAEquipmentWidget::NavigateRight()
{
	UDAWidget::NavigateRight();
	UpdateItemInfoPanel();
}

void UDAEquipmentWidget::NavigateDown()
{
	UDAWidget::NavigateDown();
	UpdateItemInfoPanel();
}

void UDAEquipmentWidget::NavigateLeft()
{
	UDAWidget::NavigateLeft();
	UpdateItemInfoPanel();
}

