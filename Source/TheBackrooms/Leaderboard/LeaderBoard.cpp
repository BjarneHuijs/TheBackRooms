// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderBoard.h"

#include "Kismet/GameplayStatics.h"

ULeaderBoard::ULeaderBoard()
{
    m_SaveSlotName = TEXT("Leaderboard");
    m_UserIndex = 0;
}

FString ULeaderBoard::GetSaveSlotName() const
{
    return m_SaveSlotName;
}

uint32 ULeaderBoard::GetUserIndex() const
{
    return m_UserIndex;
}

void ULeaderBoard::SaveNewScore(const FPlayerRecord& player)
{
    const int nrOfRecords{ m_Records.Num() };
  
        if (nrOfRecords == 0)
        {
            m_Records.Add(player);
        }

        else
        {
            for (int i{}; i < nrOfRecords; i++)
            {
                if (player.PlayerScore >= m_Records[i].PlayerScore)
                {
                    m_Records.Insert(player, i);
                    break;
                }
            }

        	if(m_Records.Num() > 10)
        	{
                m_Records.RemoveAt(m_Records.Num() - 1);
        	}
        }
    
  
}

bool ULeaderBoard::IsNewLeaderboardScore(int score)
{
    const int nrOfRecords{ m_Records.Num() };
	
    if (nrOfRecords > 0) 
    {
    	if(nrOfRecords < 10)
    	{
            //return true;
    	}
    	
        for (FPlayerRecord record : m_Records)
        {
            if (score >= record.PlayerScore)
            {
                return true;
            }
        }
    }else
    {
        return true;
    }
	
    return false;
}

const FPlayerRecord& ULeaderBoard::GetHighestRecord() const
{
    return m_Records.Top();
}

TArray<FPlayerRecord> ULeaderBoard::GetRecords() const
{
    return m_Records;
}
