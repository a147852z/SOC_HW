-- counter_axi.vhd
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter_axi is
    Port (
        clk           : in  std_logic;
        reset         : in  std_logic;
        btn           : in  std_logic;
        threshold_val : in std_logic_vector(7 downto 0);
        O_LED         : out std_logic_vector(7 downto 0)
    );
end counter_axi;

architecture Behavioral of counter_axi is
    signal count       : std_logic_vector(7 downto 0) := (others => '0');
    signal enable      : std_logic := '0';
    signal display     : std_logic_vector(7 downto 0);

    -- 除頻器 (使用 counter bit 來產生 slow_clk)
    signal tmp          : std_logic_vector(31 downto 0) := (others => '0');
    signal slow_clk     : std_logic := '0';
begin

    -- 除頻邏輯：讓 tmp 不斷累加，取其中一個位元作為慢速時脈
    process(clk, reset)
    begin
        if reset = '1' then
            tmp <= (others => '0');
        elsif rising_edge(clk) then
            tmp <= tmp + 1;
        end if;
    end process;

    slow_clk <= tmp(24);  -- 取第25位當作慢速時脈輸出（視時脈頻率調整）

    -- 啟動使能（使用 btn 控制）
    process(slow_clk)
    begin
        if rising_edge(slow_clk) then
            enable <= btn;
        end if;
    end process;

    -- 計數器
    process(slow_clk, reset)
    begin
        if reset = '1' then
            count <= (others => '0');
        elsif rising_edge(slow_clk) then
            if enable = '1' then
                if count = threshold_val then
                    count <= (others => '0');
                else
                    count <= count + 1;
                end if;
            end if;
        end if;
    end process;

    -- 每 2-bit 視為一組 4進制值控制 LED
    process(count)
        variable i : integer;
        variable led_map : std_logic_vector(7 downto 0);
    begin
        led_map := (others => '0');
        for i in 0 to 3 loop
            case count(i*2+1 downto i*2) is
                -- when "00" => led_map(i*2+0) := '1';
                -- when "01" => led_map(i*2+1) := '1';
                -- when "10" => led_map(i*2+0) := '1'; led_map(i*2+1) := '1';
                -- when others => null;
                when "00" => null;  -- 不亮
                when "01" => led_map(i*2+0) := '1';
                when "10" => led_map(i*2+1) := '1';
                when "11" => led_map(i*2+0) := '1'; led_map(i*2+1) := '1';
            end case;
        end loop;
        display <= led_map;
    end process;

    -- 輸出到 LED
    O_LED <= display;

end Behavioral;
