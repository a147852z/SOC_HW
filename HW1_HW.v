library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity binary_counter_8bit is
    Port (
        clk   : in  STD_LOGIC;
        reset : in  STD_LOGIC;
        q     : out STD_LOGIC_VECTOR(7 downto 0)
    );
end binary_counter_8bit;

architecture Behavioral of binary_counter_8bit is
    signal count : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
begin

    process(clk, reset)
    begin
        if reset = '1' then
            count <= (others => '0');
        elsif rising_edge(clk) then
            count <= count + 1;
        end if;
    end process;

    q <= count;

end Behavioral;
