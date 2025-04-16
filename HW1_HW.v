-- counter_axi.vhd
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter_axi is
    Port (
        clk      : in  std_logic;
        reset    : in  std_logic;
        btn      : in  std_logic;
        O_LED    : out std_logic_vector(7 downto 0)
    );
end counter_axi;

architecture Behavioral of counter_axi is
    signal threshold : std_logic_vector(7 downto 0) := (others => '0');
    signal count     : std_logic_vector(7 downto 0) := (others => '0');
    signal enable    : std_logic := '0';
begin

    -- 啟動使能（使用 btn 控制）
    process(clk)
    begin
        if rising_edge(clk) then
            enable <= btn;
        end if;
    end process;

    -- 計數器
    process(clk, reset)
    begin
        if reset = '1' then
            count <= (others => '0');
        elsif rising_edge(clk) then
            if enable = '1' then
                if count = threshold then
                    count <= (others => '0');
                else
                    count <= count + 1;
                end if;
            end if;
        end if;
    end process;

    -- 將計數值輸出至 LED
    O_LED <= count;

end Behavioral;
